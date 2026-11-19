#include "main.h"

int main()
{
	cs_Initial();
	timeBeginPeriod(1);
	QueryPerformanceFrequency(&qpcFreq);
	QueryPerformanceCounter(&qpcTick);
	lastTick = qpcTick.QuadPart;

	while (!gameExit)
	{
		switch (scene)
		{
		case TITLE:
			GoTitle();
			break;
		case GAME:
			GoGame();
			break;
		case LOAD:
			GoLoad();
			break;
		case EXIT:
			GoExit();
			break;
		}
	}
}