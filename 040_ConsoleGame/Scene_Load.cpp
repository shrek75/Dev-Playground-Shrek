#include "main.h"
#include "textParser.h"

void GoLoad()
{
	//이곳에서도 Update와 Render가 필요할까..
	//아니 필요가없다. 빨리 로딩이나 해야지

	TextParser stageList(STAGE_LIST_FILE);
	char buf[MAX_PATH + 1];

	//2번째줄의 15번째문자부터 totalStage임. 일단 이런식으로 진행
	stageList.GetNextString(buf, sizeof(buf));
	stageList.GetNextString(buf, sizeof(buf));
	int totalStage = atoi(&buf[14]);
	
	//stage의 총개수만큼 stage 파일명을 저장할수 있는 메모리 할당.
	// pStage를 전역으로 빼야겠네.
	char (*pStage)[MAX_PATH + 1] = (char (*)[MAX_PATH + 1])malloc(totalStage * (sizeof(char) * (MAX_PATH + 1)));
	if (pStage == nullptr) return;

	//stage 파일명 넣어주기.
	for (int i = 0; i < totalStage; i++)
	{
		stageList.GetNextString(buf, sizeof(buf));
		strcpy_s(pStage[i], sizeof(pStage[i]), buf);
	}

	//Enemy 로딩

	//Pattern 로딩

	




	//GAME SCENE으로 전환한다.
	scene = GAME;
	//현재 SCENE에서 지연된 Tick이 다음Scene에 영향을 가지 않게끔 tick을 초기화 시켜준다.
	QueryPerformanceCounter(&qpcTick);
	lastTick = qpcTick.QuadPart;
}