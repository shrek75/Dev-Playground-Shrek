#include <iostream>
#include <Windows.h>
#include <stack>
#include <queue>

using namespace std;

#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 20

struct Node
{
	BOOL _isVisited; //방문여부
	int _parentX; //나를 방문한 노드
	int _parentY; //나를 방문한 노드

};

struct Pos
{
	int X;
	int Y;
};
const char Original[SCREEN_HEIGHT][SCREEN_WIDTH] = {
	{ ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ' },
	{ ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X', ' ', 'X', ' ' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', 'X', 'X', ' ', 'X', ' ', 'X', 'X', 'X', 'X', 'X', 'X' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', ' ', ' ' },
	{ ' ', 'X', ' ', 'X', 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', ' ', ' ' }
};

char Copy[SCREEN_HEIGHT][SCREEN_WIDTH];

Node nodeArr[SCREEN_HEIGHT][SCREEN_WIDTH];

void DFS(int, int, int, int);
void BFS(int, int, int, int);

int main()
{
	//DFS(0, 0, 19, 9);
	BFS(0, 0, 19, 9);

}

//길찾기 완료후 길을 Render하는 함수
void PrintPath(int x, int y)
{
	//목적지 거슬러올라가서 길찍어주고
	if (x != -1 && y != -1)
	{
		Copy[y][x] = '.';
		PrintPath(nodeArr[y][x]._parentX, nodeArr[y][x]._parentY);
	}

	//맵과 길을 함께출력
	else
	{
		system("cls");
		for (int i = 0; i < SCREEN_HEIGHT; i++)
		{
			for (int j = 0; j < SCREEN_WIDTH; j++)
				printf("%c", Copy[i][j]);
			printf("\n");
		}

		Sleep(10000);
	}
}

//길찾기 중간과정 Render하는 함수
void Render(int x, int y)
{
	system("cls");

	Copy[y][x] = '*';

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
			printf("%c", Copy[i][j]);
		printf("\n");
	}
	
	Sleep(50);
}

void DFS(int startX, int startY, int endX, int endY)
{
	memcpy(Copy, Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);

	int x = startX;
	int y = startY;

	nodeArr[startY][startX]._parentX = -1;
	nodeArr[startY][startX]._parentY = -1;

	stack<Pos> nodeStack;
	nodeStack.push({ startX,startY });

	while (1)
	{
		if (nodeStack.empty()) break;
		x = nodeStack.top().X;
		y = nodeStack.top().Y;
		nodeStack.pop();

		if (nodeArr[y][x]._isVisited) continue;

		//isVisited설정
		nodeArr[y][x]._isVisited = TRUE;

		//DFS 과정 Render
		Render(x,y);

		//목적지 찾음!
		if (x == endX && y == endY) break;

		//동서남북크로스 push
		Pos dPos[4] = { {1,0},{-1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4; i++)
		{
			//가야할 노드 좌표 설정
			int newX = x + dPos[i].X;
			int newY = y + dPos[i].Y;

			//범위검사
			if (newX < 0 || newX >= SCREEN_WIDTH || newY < 0 || newY >= SCREEN_HEIGHT)
				continue;

			//이미 방문한노드인지 검사
			if (nodeArr[newY][newX]._isVisited)
				continue;

			//못가는길인지 확인
			if (Original[newY][newX] == 'X')
				continue;

			//이게 stack구조라서 계속 덮어쓰는구나. parent랑 visited랑.. visited설정을 pop할때 해야겠네
			// 근데 stack이라서 이건 여기에 parent설정을해도되는데 queue는?
			// queue는 만들때부터 isvisited를 해서 넣어줘야겠는데..
			//Parent설정
			nodeArr[newY][newX]._parentX = x;
			nodeArr[newY][newX]._parentY = y;

			

			//push
			nodeStack.push({ newX,newY });
		}
	}

	//목적지를 찾는데  실패했다면
	if (x != endX || y != endY)
	{
		printf("못찾음\n");
		return;
	}

	memcpy(Copy, Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);
	PrintPath(x, y);

}

void BFS(int startX, int startY, int endX, int endY)
{
	memcpy(Copy, Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);

	int x = startX;
	int y = startY;

	nodeArr[startY][startX]._parentX = -1;
	nodeArr[startY][startX]._parentY = -1;

	queue<Pos> nodeQueue;
	nodeQueue.push({ startX,startY });

	while (1)
	{
		if (nodeQueue.empty()) break;
		x = nodeQueue.front().X;
		y = nodeQueue.front().Y;
		nodeQueue.pop();

		if (nodeArr[y][x]._isVisited) continue;

		//isVisited설정
		//nodeArr[y][x]._isVisited = TRUE;

		//BFS 과정 Render
		Render(x, y);

		//목적지 찾음!
		if (x == endX && y == endY) break;

		//동서남북크로스 push
		Pos dPos[4] = { {1,0},{-1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4; i++)
		{
			//가야할 노드 좌표 설정
			int newX = x + dPos[i].X;
			int newY = y + dPos[i].Y;

			//범위검사
			if (newX < 0 || newX >= SCREEN_WIDTH || newY < 0 || newY >= SCREEN_HEIGHT)
				continue;

			//이미 방문한노드인지 검사
			if (nodeArr[newY][newX]._isVisited)
				continue;

			//못가는길인지 확인
			if (Original[newY][newX] == 'X')
				continue;

			//이게 stack구조라서 계속 덮어쓰는구나. parent랑 visited랑.. visited설정을 pop할때 해야겠네
			// 근데 stack이라서 이건 여기에 parent설정을해도되는데 queue는?
			// queue는 만들때부터 isvisited를 해서 넣어줘야겠는데..
			
			nodeArr[y][x]._isVisited = TRUE;
			
			//Parent설정
			nodeArr[newY][newX]._parentX = x;
			nodeArr[newY][newX]._parentY = y;



			//push
			nodeQueue.push({ newX,newY });
		}
	}

	//목적지를 찾는데  실패했다면
	if (x != endX || y != endY)
	{
		printf("못찾음\n");
		return;
	}

	memcpy(Copy, Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);
	PrintPath(x, y);

}