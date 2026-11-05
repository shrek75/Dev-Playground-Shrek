#include "PathFinding.h"

void PathFinding::InitMap()
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
			Node node = _map[x + y * _screenWidth];
			node._x = x;
			node._y = y;
			node._parent = nullptr;
			node._isTraveled = FALSE;
			node._isReserved = FALSE;
			node._isObstacle = FALSE;
			node._traveledDistance = 0xFFFFFFFF;
			node._expectedDistance = 0xFFFFFFFF;
		}
	}
}

PathFinding::PathFinding()
{
	InitMap();
}
PathFinding::~PathFinding()
{
	if (_map != nullptr)
		free(_map);
}