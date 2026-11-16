#include "main.h"
#include <iostream>

void Update();
void Render();

void GoTitle()
{
	QueryPerformanceCounter(&qpcTick);
	if (qpcTick.QuadPart > lastTick + GAME_FPS_100NS)
	{
		lastTick += GAME_FPS_100NS;
		Update();
		Render();
	}
}

void Update()
{
	updateCalls++;
	if (GetAsyncKeyState(VK_SPACE))
		scene = GAME;
}

void Render()
{
	renderCalls++;
	Buffer_Clear();

	const char titleMsg[] = "Console Game, Made by, Kim Tae Uk.";
	static int msgIndex = 0;

	DWORD tick = timeGetTime(); //매Render마다 TimeGetTime
	static DWORD msgTick = tick; //마지막 타이틀msg 처리 tick
	static DWORD fpsTick = tick; //마지막 fps처리 tick

	//타이틀 메세지 출력 처리
	if (tick > msgTick + 200)
	{
		msgTick += 200;
		if (msgIndex != strlen(titleMsg) - 1)
			msgIndex++;
	}

	for (int i = 0; i <= msgIndex; i++)
	{
		Sprite_Draw(i, 2, titleMsg[i]);
	}

	//상단 fps출력 처리
	static char fpsMsg[30] = { 0 };
	if (tick > fpsTick + 1000)
	{
		fpsTick += 1000;
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
