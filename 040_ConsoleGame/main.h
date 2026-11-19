#pragma once
#include <Windows.h>
#include "Console.h"
#include <iostream>
#pragma comment(lib, "winmm.lib")

#define GAME_FPS 50 //게임의 초당 Update 횟수
#define GAME_FPS_100NS (1000 / GAME_FPS * 1000 * 10) //"GAME_FPS"를 맞추려면 얼마마다 돌아야하는지 100ns단위로 변환한 값 

#define STAGE_DIR "stage/"
#define STAGE_LIST_FILE "stage/_stage_list.txt" //스테이지 정보 파일
#define PATTERN_DIR "pattern/"
#define PATTERN_LIST_FILE "_pattern_list.txt"
#define ENEMY_DIR "enemy/"
#define ENEMY_LIST_FILE "_enemy_list.txt" //enemy 정보 파일

#define MAX_ENEMY_BULLETS 100 //화면속 상대 총알 MAX개수
#define MAX_PLAYER_BULLETS 30 //화면속 내 총알 MAX 개수
#define MAX_ENEMY_NUMS 200

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

inline char (*pStageFileName)[MAX_PATH + 1] = nullptr; //각 스테이지들의 파일명을 가리키는 포인터.
inline int totalStage = 0; //총 스테이지 개수

void GoTitle();
void GoGame();
void GoExit();
void GoLoad();


struct ENEMY_PATTERN
{
	char _patternName[MAX_PATH + 1]; //패턴이름 (패턴파일명으로 하였음.) 
	char _movePattern[64];
	char _attkPattern[64];
	int _movePatternSize; // move 패턴의 사이즈 (0 ~ size-1) 까지 계속해서 반복한다.
	int _attkPatternSize; // attack 패턴의 사이즈 (0 ~ size-1) 까지 계속해서 반복한다.
};
inline ENEMY_PATTERN* patternInfo = nullptr; //Pattern 정보 배열
inline int totalPattern = 0; //Pattern이 총 몇종류인지

struct ENEMY
{
	BOOL _isUsed; //배열로 쓸거라 사용중인지 변수 
	char _symbol;
	ENEMY_PATTERN* _pattern;
	int _hp;
	int _score;
	int _power;
	int _x;
	int _y;
	int _movePatternIndex; //현재 무브패턴의 몇번째에 있는지
	int _attkPatternIndex; //현재 어택패턴의 몇번째에 있는지
};

inline int totalEnemyInfo = 0; //Enemy가 총 몇종류인지.
inline ENEMY* enemyInfo = nullptr; //ENEMY 정보를 담은 배열


inline int nowStage = 0; //현재스테이지
inline BOOL isStageLoaded = FALSE; //현재스테이지가 로딩되었는지
inline ENEMY enemyList[MAX_ENEMY_NUMS] = { 0 }; //Enemy List
inline int aliveEnemyNums = 0;

struct Player
{
	char _symbol;
	int _hp;
	int _score;
	int _power;
	int _x;
	int _y;
	int _attackCoolDown;   //어택쿨타임
	int _nowAttackCoolDown; //현재 쿨타임 계산용
	int _moveCoolDown;    //움직이는거 쿨타임
	int _nowMoveCoolDown; //현재 쿨타임 계산용
};

inline Player player;

struct Bullet
{
	BOOL _isUsed;         //배열로 쓸거라, 활성화 ON OFF
	char _symbol;
	int _power;
	int _x;
	int _y;
	int _moveCoolDown;    //움직이는거 쿨타임
	int _nowMoveCoolDown; //현재 쿨타임 계산용
	int _moveX;           //움직이는 방향
	int _moveY;           //움직이는 방향
};

inline Bullet playerBulletList[MAX_PLAYER_BULLETS];
inline Bullet enemyBulletList[MAX_ENEMY_BULLETS];