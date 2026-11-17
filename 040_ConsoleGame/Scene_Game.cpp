#include "main.h"

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

BOOL UpdateGame()
{
	//스페이스바 누를 시 GAME SCENE으로 전환.
	if (GetAsyncKeyState(VK_SPACE))
	{
		scene = EXIT;
		return FALSE;
	}
	return TRUE;
}

//static, const를 많이 사용하게 된다.
//함수가 계속 해서 호출되는 구조이고, 이전 값을 기억하기 위해선 그럴 수 밖에 없다.
void RenderGame()
{	
	Buffer_Clear();

	const char titleMsg[] = "Console Game, Made by, Kim Tae Uk.";
	static int msgIndex = 0;

	//일정 시간마다 타이틀을 출력하기 위해 매 Render마다 timeGetTime()으로 시간을 얻어온다.
	DWORD tick = timeGetTime();

	static DWORD msgLastTick = tick; //타이틀msg 를 처리한 마지막 tick수.
	static DWORD fpsLastTick = tick; //상단fps표기 를 처리한 마지막 tick수.

	//타이틀 메세지 출력 처리(ms단위)
	if (tick > msgLastTick + 200)
	{
		msgLastTick += 200;
		if (msgIndex != strlen(titleMsg) - 1)
			msgIndex++;
	}

	for (int i = 0; i <= msgIndex; i++)
	{
		Sprite_Draw(i, 2, titleMsg[i]);
	}

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


	Buffer_Flip();
}