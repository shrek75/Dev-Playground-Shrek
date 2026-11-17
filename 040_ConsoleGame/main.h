#pragma once
#include <Windows.h>
#include "Console.h"
#include <iostream>
#pragma comment(lib, "winmm.lib")

#define GAME_FPS 50 //게임의 초당 Update 횟수
#define GAME_FPS_100NS (GAME_FPS * 1000 * 10) //"GAME_FPS"를 100ns단위로 변환한 값 

#define STAGE_LIST_FILE "stage/_stage_list.txt" //스테이지 정보 파일
#define ENEMY_LIST_FILE "enemy/_enemy_list.txt" //enemy 정보 파일

enum SCENE
{
	TITLE,
	GAME,
	EXIT,
	LOAD
};

inline SCENE scene = TITLE;   //현재 scene
inline BOOL gameExit = FALSE; //프로그램 종료 bool변수
inline LARGE_INTEGER qpcFreq = {};
inline LARGE_INTEGER qpcTick = {};  //QPC 호출마다 갱신
inline LONGLONG lastTick = 0; //과거에 update시 사용한 qpcTick 값.
inline int updateCalls = 0;
inline int renderCalls = 0;


void GoTitle();
void GoGame();
void GoExit();
void GoLoad();