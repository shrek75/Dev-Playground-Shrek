#pragma once

#include <Windows.h>
#include <iostream>
#include <stack>

#define CELL_SIZE 30 //창에 노드하나를 그릴 정사각형 사이즈. 이 사이즈 기준으로 픽셀을 판단하여 클릭한 노드를 알아낸다.

struct Node
{
	DWORD _traveledDistance; //지금까지 이동거리
	DWORD _expectedDistance; //목적지까지 예상거리
	DWORD _isTraveled;       //이미 탐색했는지.
	DWORD _isReserved;       //탐색의 후보에 올랐는지.
	
	//Node를 2차원배열에 좌표순서대로 저장할 거라, 굳이 좌표를 기록할 필요는 없긴 하다.
	int _x; // Node의 x좌표
	int _y; // Node의 y좌표
	
	BOOL _isObstacle;       //이 노드가 장애물인지 아닌지.

	Node* _parent; //현재 노드를 탐색한 부모노드.
};


class PathFinding
{

public:
	static DWORD GetScreenHeight() { return _screenHeight; }
	static DWORD GetScreenWidth() { return _screenWidth; }
	
	// 시작 노드를 설정한다. row: Y행 / col: X열
	static BOOL SetStartNode(DWORD row, DWORD col);
	// 도착 노드를 설정한다. row: Y행 / col: X열
	static BOOL SetEndNode(DWORD row, DWORD col);
	// 시작 노드의 행열 정보를 가져온다.
	static BOOL GetStartNode(DWORD* row, DWORD* col);
	// 도착 노드의 행열 정보를 가져온다.
	static BOOL GetEndNode(DWORD* row, DWORD* col);
	// Y행 X열의 노드정보를 가져온다.
	static BOOL GetNode(DWORD row, DWORD col, const Node** node);

	static BOOL SetObstacleNode(DWORD row, DWORD col,BOOL isObstacle);

	//Node들을 할당하고, 초기화를 수행한다. 
	static void Init();
	static void DeInit();

	static DWORD FindPath();


	PathFinding();
	~PathFinding();

private:

	inline static BOOL _isStarted; //길찾기가 진행중인지 나타내는 변수

	inline static DWORD _screenHeight = 20; // y방향 Node 개수.
	inline static DWORD _screenWidth = 40;  // x방향 Node 개수.

	inline static Node* _map = nullptr; // Node의 2차원배열로 맵을 구현했다.
	inline static Node* _startNode = nullptr;  //출발점
	inline static Node* _endNode = nullptr;    //도착점

	inline static std::stack<Node*> _nodeStack; //길찾기 과정에서 탐색할 노드를 담을 스택.
};