#include "PathFinding.h"


void PathFinding::Init()
{
	if (_map != nullptr)
		free(_map);

	//Node들을 할당한다.
	_map = (Node*)malloc(sizeof(Node) * _screenWidth * _screenHeight);
	if (_map == nullptr) return;

	//각 Node를 초기화하는 작업
	for (DWORD y = 0; y < _screenHeight; y++)
	{
		for (DWORD x = 0; x < _screenWidth; x++)
		{
			Node* node = &_map[x + y * _screenWidth];
			node->_x = x;
			node->_y = y;
			node->_parent = nullptr;
			node->_isTraveled = FALSE;
			node->_isReserved = FALSE;
			node->_isObstacle = FALSE;
			node->_traveledDistance = 0xFFFFFFFF;
			node->_expectedDistance = 0xFFFFFFFF;
		}
	}

	//노드 스택 초기화
	while (!_nodeStack.empty())
		_nodeStack.pop();

	_isStarted = FALSE;
}

void PathFinding::DeInit()
{
	if (_map != nullptr)
		free(_map);
}

//Static으로 쓸거라서 생성자가 호출안되는구나
PathFinding::PathFinding()
{
	Init();
}
//Static으로 쓸거라서 소멸자도 호출안되는구나
PathFinding::~PathFinding()
{
	DeInit();
}

BOOL PathFinding::SetStartNode(DWORD row, DWORD col)
{
	// 이미 시작한 길찾기가 있다면 설정불가
	if (_isStarted) return FALSE;

	//노드의 범위 검사
	if (row >= _screenHeight || col >= _screenWidth) return FALSE;

	_startNode = &_map[row * _screenWidth + col];

	//탐색해야할 노드스택 초기화.
	while (!_nodeStack.empty())
		_nodeStack.pop();
	_nodeStack.push(_startNode);

	return TRUE;
}

BOOL PathFinding::SetEndNode(DWORD row, DWORD col)
{
	// 이미 시작한 길찾기가 있다면 설정불가
	if (_isStarted) return FALSE;

	//노드의 범위 검사
	if (row >= _screenHeight || col >= _screenWidth) return FALSE;

	_endNode = &_map[row * _screenWidth + col];
	return TRUE;
}
DWORD PathFinding::FindPath()
{
	//DFS
	
	//첫 길찾기의 시작일 때 예외처리
	if (!_isStarted)
	{
		//출발,도착점 설정 확인
		if (_startNode == nullptr || _endNode == nullptr) return 0;

		//이미 도착했는지 확인
		if (_nodeStack.empty()) return 0;

		_isStarted = TRUE;
	}
	
	//길 못찾았는지 확인
	if (_nodeStack.empty())
	{
		_isStarted = FALSE;
		return 0;
	}
	//탐색해야할 노드 설정
	Node* traveledNode = _nodeStack.top();
	_nodeStack.pop();
	traveledNode->_isTraveled = TRUE;

	//도착점에 도착했을 때
	if (traveledNode == _endNode)
	{
		_isStarted = FALSE;
		while (!_nodeStack.empty())
			_nodeStack.pop();
		return 1;
	}

	//동서남북으로 탐색후보 넣어주기
	int dX[4] = { 0,-1,0,1 };
	int dY[4] = { 1,0,-1,0 };
	for (int i = 0; i < 4; i++)
	{
		int newX = traveledNode->_x + dX[i]; //새로 탐색해야할 X좌표
		int newY = traveledNode->_y + dY[i]; //새로 탐색해야할 Y좌표
		if (newX < 0 || newX >= (int)_screenWidth) continue;
		if (newY < 0 || newY >= (int)_screenHeight) continue;
		Node* newNode = &_map[newX + newY * _screenWidth]; //새로탐색해야할 노드

		//해당노드를 탐색해야하는지 확인하기
		if (newNode->_isObstacle) continue;
		if (newNode->_isReserved) continue;
		if (newNode->_isTraveled) continue;
		
		//해당노드를 탐색의 후보에 넣어준다.
		newNode->_isReserved = TRUE;
		newNode->_parent = traveledNode;
		newNode->_traveledDistance += 1;
		_nodeStack.push(newNode);
	}

	return 0;
}

BOOL PathFinding::GetStartNode(DWORD* row, DWORD* col)
{
	if (_startNode == nullptr) return FALSE;
	if (row == nullptr || col == nullptr) return FALSE;
	*row = _startNode->_y;
	*col = _startNode->_x;
	return TRUE;
}

BOOL PathFinding::GetEndNode(DWORD* row, DWORD* col)
{
	if (_endNode == nullptr) return FALSE;
	if (row == nullptr || col == nullptr) return FALSE;
	*row = _endNode->_y;
	*col = _endNode->_x;
	return TRUE;
}

BOOL PathFinding::GetNode(DWORD row, DWORD col, const Node** node)
{
	if (_map == nullptr) return FALSE;

	//노드의 범위 검사
	if (row >= _screenHeight || col >= _screenWidth) return FALSE;

	//사용자 입장에서 Node*를 받아야하니, 인자로 Node**를 받아야 Node*를 넣어줄 수 있다.
	*node = &_map[row * _screenWidth + col];

	return TRUE;
}

BOOL PathFinding::SetObstacleNode(DWORD row, DWORD col, BOOL isObstacle)
{
	if (_map == nullptr) return FALSE;
	if (row >= _screenHeight || col >= _screenWidth) return FALSE;

	_map[row * _screenWidth + col]._isObstacle = isObstacle;
	return TRUE;
}