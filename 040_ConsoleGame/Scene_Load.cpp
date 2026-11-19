#include "main.h"
#include "textParser.h"

void GoLoad()
{
	//이곳에서도 Update와 Render가 필요할까..
	//아니 필요가없다. 빨리 로딩이나 해야지


#pragma region Stage 정보 로딩

	//Stage 정보 로딩
	TextParser stageList(STAGE_LIST_FILE);
	if (stageList.GetFileSize() == 0)
		return;

	char buf[MAX_PATH + 1];

	//2번째줄의 15번째문자부터 totalStage임. 일단 이런식으로 진행
	stageList.GetNextString(buf, sizeof(buf));
	stageList.GetNextString(buf, sizeof(buf));
	totalStage = atoi(&buf[14]);
	stageList.GetNextString(buf, sizeof(buf));

	//stage의 총개수만큼 stage 파일명을 저장할수 있는 메모리 할당.
	pStageFileName = (char (*)[MAX_PATH + 1])malloc(totalStage * (sizeof(char) * (MAX_PATH + 1)));
	if (pStageFileName == nullptr) return;

	//stage 파일명 넣어주기.
	//파일 로딩예외처리 안함. 파일똑바로 작성하시오. 
	for (int i = 0; i < totalStage; i++)
	{
		stageList.GetNextString(buf, sizeof(buf));
		strcpy_s(pStageFileName[i], sizeof(pStageFileName[i]), buf);
	}

#pragma endregion

#pragma region Enemy Pattern 로딩
	//Enemy Pattern 로딩
	char patternList[MAX_PATH + 1];
	sprintf_s(patternList, "%s%s", PATTERN_DIR, PATTERN_LIST_FILE);
	TextParser pl(patternList);

	//PatternList 파일열기 실패!
	if (pl.GetFileSize() == 0)
		return;

	pl.GetNextString(buf, sizeof(buf));
	pl.GetNextString(buf, sizeof(buf));
	totalPattern = atoi(&buf[16]);
	pl.GetNextString(buf, sizeof(buf));

	patternInfo = (ENEMY_PATTERN*)malloc(sizeof(ENEMY_PATTERN) * totalPattern);
	if (patternInfo == nullptr) return;
	
	for (int i = 0; i < totalPattern; i++)
	{
		//Pattern 파일이름을 불러온다.
		pl.GetNextString(buf, sizeof(buf));
		char patternFile[MAX_PATH + 1];
		sprintf_s(patternFile, "%s%s", PATTERN_DIR, buf);
		//패턴 파일을 연다
		TextParser p(patternFile);

		//파일열기에 실패했다면
		if (p.GetFileSize() == 0)
		{
			totalPattern--;
			i--;
			continue;
		}

		//패턴파일을 로딩한다.
		char str[MAX_PATH + 1];

		//patternName
		strcpy_s(patternInfo[i]._patternName, buf);

		//movePattern
		int size = p.GetNextString(str, sizeof(str));
		strcpy_s(patternInfo[i]._movePattern, &str[6]);

		//movePatternSize
		patternInfo[i]._movePatternSize = size - 6;

		//attackPattern
		size = p.GetNextString(str, sizeof(str));
		strcpy_s(patternInfo[i]._attkPattern, &str[6]);

		//attackPatternSize
		patternInfo[i]._attkPatternSize = size - 6;

	}
#pragma endregion

#pragma region Enemy 로딩

	//Enemy 로딩
	char enemyFile[MAX_PATH + 1];
	sprintf_s(enemyFile, "%s%s", ENEMY_DIR, ENEMY_LIST_FILE);
	TextParser enemyList(enemyFile);
	if (enemyList.GetFileSize() == 0) return;

	enemyList.GetNextString(buf, sizeof(buf));
	enemyList.GetNextString(buf, sizeof(buf));
	totalEnemyInfo = atoi(&buf[14]);
	enemyList.GetNextString(buf, sizeof(buf));

	//enemy정보들을 담을 배열 할당.
	enemyInfo = (ENEMY*)malloc(sizeof(ENEMY) * totalEnemyInfo);
	if (enemyInfo == nullptr)return;

	//파일 로딩예외처리 안함. 파일똑바로 작성하시오. 
	for (int i = 0; i < totalEnemyInfo; i++)
	{
		//Enemy 파일이름 불러온다.
		enemyList.GetNextString(buf, sizeof(buf));
		char enemyFile[MAX_PATH + 1];
		sprintf_s(enemyFile, "%s%s", ENEMY_DIR, buf);
		//그 Enemy파일을 연다.
		TextParser enemy(enemyFile);

		if (enemy.GetFileSize() == 0)
		{
			totalEnemyInfo--;
			i--;
			continue;
		}

		char str[MAX_PATH + 1];

		//symbol
		enemy.GetNextString(str, sizeof(str));
		enemyInfo[i]._symbol = str[9];

		//pattern
		enemy.GetNextString(str, sizeof(str));
		ENEMY_PATTERN* tempP = nullptr;

		//patternName에 해당하는 패턴정보가 있는지 순회해봄. 
		for (int j = 0; j < totalPattern; j++)
		{
			if (strcmp(&str[10], patternInfo[j]._patternName) == 0)
			{
				tempP = &patternInfo[j];
				break;
			}
		}

		//찾았으면 저장하고, 못찾았으면 skip.
		if (tempP != nullptr)
			enemyInfo[i]._pattern = tempP;
		else
		{
			totalEnemyInfo--;
			i--;
			continue;
		}

		//hp
		enemy.GetNextString(str, sizeof(str));
		enemyInfo[i]._hp = atoi(&str[5]);

		//score
		enemy.GetNextString(str, sizeof(str));
		enemyInfo[i]._score = atoi(&str[8]);

		//power
		enemy.GetNextString(str, sizeof(str));
		enemyInfo[i]._power = atoi(&str[8]);
	}

#pragma endregion

	


	//GAME SCENE으로 전환한다.
	scene = GAME;
	//현재 SCENE에서 지연된 Tick이 다음Scene에 영향을 가지 않게끔 tick을 초기화 시켜준다.
	QueryPerformanceCounter(&qpcTick);
	lastTick = qpcTick.QuadPart;
}