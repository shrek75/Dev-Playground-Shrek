#include "main.h"
#include "textParser.h"

//Scene전환이 필요할시 Render을 안하기 위해 BOOL값을 return한다. FALSE: SCENE전환 예약.
BOOL UpdateGame();
void RenderGame();

void GoGame()
{
	//현재의 틱을 가져온다.
	QueryPerformanceCounter(&qpcTick);

	// Frame을 돌려야할 때가 되었다면 Update!
	// [현재틱 > 마지막에 처리한 tick + GAME FPS] 으로 계산하면 된다.
	if (qpcTick.QuadPart > lastTick + GAME_FPS_100NS)
	{
		//마지막 Update Tick을 갱신한다.
		lastTick += GAME_FPS_100NS;

		// Update()돌려준다.
		// Scene전환이 예고되면 return한다.
		updateCalls++;
		if (!UpdateGame()) return;
	}

	// 1프레임을 돌린 후지만, 다음 프레임을 또 돌려야하는 상황이라면(즉, 프레임이 밀리고 있다면) 
	// Render는 포기한다.
	// 프레임이 밀리고 있지않을 때만 Render를 수행한다.

	// 위의 Update구문 내부에서, 아래의if문을 수행하면, 프레임이 밀리지않을때 (UpdateCalls == RenderCalls) 가 된다.
	// 지금 같은 2D게임에서는 그게 맞지만, 성능이 좋을 때 RenderCall횟수가 바뀌는 것을 확인하고 싶어서 따로 분리했다.
	if (qpcTick.QuadPart < lastTick + GAME_FPS_100NS)
	{
		renderCalls++;
		RenderGame();
	}
}

//게임 초기화
void Init()
{
	//인스턴스 저장용 배열들 초기화
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		playerBulletList[i]._isUsed = FALSE;
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		enemyBulletList[i]._isUsed = FALSE;
	}
	for (int i = 0; i < MAX_ENEMY_NUMS; i++)
	{
		enemyList[i]._isUsed = FALSE;
	}
	aliveEnemyNums = 0;

	//플레이어 초기화
	player._hp = 10;
	player._attackCoolDown = 5;
	player._moveCoolDown = 1;
	player._nowAttackCoolDown = 0;
	player._nowMoveCoolDown = 0;
	player._score = 0;
	player._symbol = '@';
	player._power = 1;
	player._x = dfSCREEN_WIDTH / 2;
	player._y = dfSCREEN_HEIGHT - 1;
}


BOOL UpdateGame()
{

#pragma region 현재스테이지 로딩
	//현재 스테이지 로딩하기
	if (!isStageLoaded)
	{
		//Stage를 모두 클리어했을 때
		if (nowStage >= totalStage)
		{
			scene = EXIT;
			return FALSE;
		}

		//첫 스테이지라면 초기화작업 (게임중간에 죽었을수도있고..)
		if (nowStage == 0)
			Init();	

		//해당스테이지 파일 열고, ENEMY 생성.
		char stageFile[MAX_PATH + 1];
		sprintf_s(stageFile, "%s%s", STAGE_DIR, pStageFileName[nowStage]);
		TextParser s(stageFile);
		if (s.GetFileSize() == 0) return FALSE;
		
		for (int y = 1; y < dfSCREEN_HEIGHT; y++)
		{
			char buf[dfSCREEN_WIDTH];
			s.GetNextString(buf, sizeof(buf));
			for (int x = 0; x < dfSCREEN_WIDTH - 1; x++)
			{
				//파일의 심볼 하나를 읽어온다.
				char symbol = buf[x];

				//해당 심볼에 해당하는 몬스터 정보가 있는지 찾아본다.
				if (symbol == ' ' || symbol == '.') continue;
				for (int i = 0; i < totalEnemyInfo; i++)
				{
					//찾았다면 Enemy를 생성한다.
					if (enemyInfo[i]._symbol == symbol)
					{
						enemyList[aliveEnemyNums]._isUsed = TRUE;
						enemyList[aliveEnemyNums]._x = x;
						enemyList[aliveEnemyNums]._y = y;
						enemyList[aliveEnemyNums]._pattern = enemyInfo[i]._pattern;
						enemyList[aliveEnemyNums]._power = enemyInfo[i]._power;
						enemyList[aliveEnemyNums]._score = enemyInfo[i]._score;
						enemyList[aliveEnemyNums]._symbol = enemyInfo[i]._symbol;
						enemyList[aliveEnemyNums]._hp = enemyInfo[i]._hp;
						enemyList[aliveEnemyNums]._movePatternIndex = 0;
						enemyList[aliveEnemyNums]._attkPatternIndex = 0;

						aliveEnemyNums++;
						break;
					}
				}
			}
		}
		

		isStageLoaded = TRUE;
	}
#pragma endregion

	//Player Bullet 이동처리
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		Bullet& bullet = playerBulletList[i];
		if (!bullet._isUsed) continue;

		//이동쿨타임처리
		if (bullet._nowMoveCoolDown != 0)
			bullet._nowMoveCoolDown--;
		if (bullet._nowMoveCoolDown == 0)
		{
			//이동
			bullet._x += bullet._moveX;
			bullet._y += bullet._moveY;
			//화면밖나갔으면 소멸
			if (bullet._x < 0 || bullet._x >= dfSCREEN_WIDTH - 1
				|| bullet._y < 1 || bullet._y >= dfSCREEN_HEIGHT)
			{
				bullet._isUsed = FALSE;
			}
			//쿨타임 지정
			bullet._nowMoveCoolDown = bullet._moveCoolDown;
		}
	}

	//Enemy Bullet 이동처리
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		Bullet& bullet = enemyBulletList[i];
		if (!bullet._isUsed) continue;

		//이동쿨타임처리
		if (bullet._nowMoveCoolDown != 0)
			bullet._nowMoveCoolDown--;
		if (bullet._nowMoveCoolDown == 0)
		{
			//이동
			bullet._x += bullet._moveX;
			bullet._y += bullet._moveY;
			//화면밖나갔으면 소멸
			if (bullet._x < 0 || bullet._x >= dfSCREEN_WIDTH - 1
				|| bullet._y < 1 || bullet._y >= dfSCREEN_HEIGHT)
			{
				bullet._isUsed = FALSE;
			}
			//쿨타임 지정
			bullet._nowMoveCoolDown = bullet._moveCoolDown;
		}
	}


	//ENEMY MOVE + ATTACK 처리
	for (int i = 0; i < MAX_ENEMY_NUMS; i++)
	{
		ENEMY& enemy = enemyList[i];
		if (!enemy._isUsed) continue;

		//MOVE
		char nextMove = enemy._pattern->_movePattern[enemy._movePatternIndex];
		switch (nextMove)
		{
		case '>':
			if (enemy._x + 1 < dfSCREEN_WIDTH - 1)
				enemy._x++;
			break;
		case '<':
			if (enemy._x - 1 >= 0)
				enemy._x--;
			break;
		}
		enemy._movePatternIndex = (enemy._movePatternIndex + 1) % enemy._pattern->_movePatternSize;

		//ATTACK
		char nextAttk = enemy._pattern->_attkPattern[enemy._attkPatternIndex];
		switch (nextAttk)
		{
		//총알생성
		case 'A':
			for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
			{
				if (enemyBulletList[i]._isUsed == FALSE)
				{
					enemyBulletList[i]._isUsed = TRUE;
					enemyBulletList[i]._moveX = 0;
					enemyBulletList[i]._moveY = 1;
					enemyBulletList[i]._x = enemy._x;
					enemyBulletList[i]._y = enemy._y;
					enemyBulletList[i]._nowMoveCoolDown = 0;
					enemyBulletList[i]._moveCoolDown = 2;
					enemyBulletList[i]._power = enemy._power;
					enemyBulletList[i]._symbol = '*';
					break;
				}
			}
			break;
		}
		enemy._attkPatternIndex = (enemy._attkPatternIndex + 1) % enemy._pattern->_attkPatternSize;
	}

	//플레이어 이동 처리
	if (player._nowMoveCoolDown != 0)
		player._nowMoveCoolDown--;
	if (player._nowMoveCoolDown == 0)
	{
		BOOL isMoved = FALSE;
		if (GetAsyncKeyState(VK_RIGHT))
		{
			player._x++;
			isMoved = TRUE;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			player._x--;
			isMoved = TRUE;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			player._y--;
			isMoved = TRUE;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			player._y++;
			isMoved = TRUE;
		}
		if (isMoved)
		{
			if (player._x == -1)
				player._x++;
			if (player._x == dfSCREEN_WIDTH - 1)
				player._x--;
			if (player._y == 0)
				player._y++;
			if (player._y == dfSCREEN_HEIGHT)
				player._y--;

			player._nowMoveCoolDown = player._moveCoolDown;
		}
	}

	//플레이어 공격 처리
	if (player._nowAttackCoolDown != 0)
		player._nowAttackCoolDown--;
	if (player._nowAttackCoolDown == 0)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
			{
				if (playerBulletList[i]._isUsed == FALSE)
				{
					playerBulletList[i]._isUsed = TRUE;
					playerBulletList[i]._moveX = 0;
					playerBulletList[i]._moveY = -1;
					playerBulletList[i]._x = player._x;
					playerBulletList[i]._y = player._y;
					playerBulletList[i]._nowMoveCoolDown = 0;
					playerBulletList[i]._moveCoolDown = 2;
					playerBulletList[i]._power = player._power;
					playerBulletList[i]._symbol = '^';
					break;
				}
			}
			player._nowAttackCoolDown = player._attackCoolDown;
		}
	}
	
	//충돌처리
	//플레이어의총알 -> ENEMY
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		if (!playerBulletList[i]._isUsed) continue;
		
		//ENEMY전체 순회해서 같은좌표의 ENEMY가있는지 찾기
		for (int j = 0; j < MAX_ENEMY_NUMS; j++)
		{
			if (!enemyList[j]._isUsed) continue;
			// player의 총알에 ENEMY가 맞았다면
			if (playerBulletList[i]._x == enemyList[j]._x && playerBulletList[i]._y == enemyList[j]._y)
			{
				//enemy의 체력을 깎는다.
				enemyList[j]._hp -= playerBulletList[i]._power;
				//총알을 없앤다.
				playerBulletList[i]._isUsed = FALSE;
				//enemy의 체력이 0이하라면 죽음처리
				if (enemyList[j]._hp <= 0)
				{
					//플레이어 점수획득
					player._score += enemyList[j]._score;
					//enemy를 없앤다.
					enemyList[j]._isUsed = FALSE;
					//살아있는 enemy수도 counting
					aliveEnemyNums--;
				}
			}
		}
	}
	//ENEMY의 총알 -> PLAYER
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		if (!enemyBulletList[i]._isUsed) continue;
		if (player._x == enemyBulletList[i]._x && player._y == enemyBulletList[i]._y)
		{
			player._hp -= enemyBulletList[i]._power;
			enemyBulletList[i]._isUsed = FALSE;
			//플레이어가 죽었다면
			if (player._hp <= 0)
			{
				nowStage = 0;
				isStageLoaded = FALSE;
				scene = GAME;
				return FALSE;
			}
		}

	}

	//스테이지를 클리어했다면.
	if (aliveEnemyNums == 0)
	{
		nowStage++;
		isStageLoaded = FALSE;
	}

	return TRUE;
}

//static, const를 많이 사용하게 된다.
//함수가 계속 해서 호출되는 구조이고, 이전 값을 기억하기 위해선 그럴 수 밖에 없다.
void RenderGame()
{	
	Buffer_Clear();

	DWORD tick = timeGetTime();
	static DWORD fpsLastTick = tick; //상단fps표기 를 처리한 마지막 tick수.

	//상단 fps출력 처리 (1000ms == 1초)
	// 사실 한 순간을 들여다봤을 때, 정확히 1초로 떨어지지는 않는다.
	// 다른코드들이 지연됐다면 1.01초가 될 수도있고, 0.99초가 될 수도 있다.
	// 하지만 마지막처리Tick을 항상 1000ms 더하기 때문에, 평균적으로는 거의 1초가 된다. 
	static char fpsMsg[30] = { 0 };
	if (tick > fpsLastTick + 1000)
	{
		fpsLastTick += 1000;
		sprintf_s(fpsMsg, "Update : %04d Render : %04d", updateCalls, renderCalls);
		updateCalls = 0;
		renderCalls = 0;
	}

	for (int i = 0; i < strlen(fpsMsg); i++)
	{
		Sprite_Draw(i, 0, fpsMsg[i]);
	}

	//STAGE, HP, SCORE 상단 출력
	char statusBar[50];
	sprintf_s(statusBar, "STAGE [%03d]     HP : %05d    SCORE : %05d", nowStage + 1, player._hp, player._score);
	for (int i = 0; i < strlen(statusBar); i++)
	{
		Sprite_Draw(dfSCREEN_WIDTH - (int)strlen(statusBar) + i - 1, 0, statusBar[i]);
	}


	//ENEMY 그려주기
	if (aliveEnemyNums > 0)
	{
		for (int i = 0; i < MAX_ENEMY_NUMS; i++)
		{
			if (!enemyList[i]._isUsed) continue;
			Sprite_Draw(enemyList[i]._x, enemyList[i]._y, enemyList[i]._symbol);
		}
	}

	//Player 그려주기
	Sprite_Draw(player._x, player._y, player._symbol);

	//Bullet 그려주기
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		if (!enemyBulletList[i]._isUsed)
			continue;
		Sprite_Draw(enemyBulletList[i]._x, enemyBulletList[i]._y, enemyBulletList[i]._symbol);
	}
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		if (!playerBulletList[i]._isUsed)
			continue;
		Sprite_Draw(playerBulletList[i]._x, playerBulletList[i]._y, playerBulletList[i]._symbol);
	}

	Buffer_Flip();


}