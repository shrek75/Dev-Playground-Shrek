#include <iostream>
#include <Windows.h>
#include <stack>
#include <queue>
#include <math.h>

using namespace std;

#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 20

struct Node
{
	BOOL _isVisited; //방문여부가 아니라 isClosed의 의미로쓰겠음. 이노드는 이제 볼필요가없다의 의미. 종결최단경로가 있다는의미.
	int _parentX; //나를 방문한 노드
	int _parentY; //나를 방문한 노드
	int _currentDistance; //지금까지 출발점으로부터의 거리
	int _predictDistance; //목적지까지 예상거리
};

int HeuristicFunc(int x1, int y1, int x2, int y2);

struct Pos
{
	int X;
	int Y;
	int seq; //삽입순서 맞출려고.. 가장 마지막에 넣은애가 우선순위큐 제일 앞에오게.
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

struct cmp
{
	bool operator()(Pos a,Pos b)
	{
		auto fa = nodeArr[a.Y][a.X]._currentDistance + nodeArr[a.Y][a.X]._predictDistance;
		auto fb = nodeArr[b.Y][b.X]._currentDistance + nodeArr[b.Y][b.X]._predictDistance;
		if (fa != fb) return fa > fb;
		return a.seq < b.seq;
	}
};
void DFS(int, int, int, int);
void BFS(int, int, int, int);
void AStar(int, int, int, int);

int main()
{
	AStar(0, 0, 19, 9);

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
	
	Sleep(300);
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

//Astar 함수에서 사용되는 휴리스틱함수 (맨헤튼?)
int HeuristicFunc(int x1, int y1, int x2, int y2)
{
	return abs(x2 - x1) + abs(y2 - y1);
}

void AStar(int startX, int startY, int endX, int endY)
{
	memcpy(Copy, Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);

	//안가본 노드는 최대거리로 설정.
	for(int i=0; i<SCREEN_HEIGHT;i++)
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			nodeArr[i][j]._currentDistance = 0x7FFFFFFF;
			nodeArr[i][j]._predictDistance = HeuristicFunc(j, i, endX, endY); //여기서 미리계산
		}
	
	int seq = 0;

	int x = startX;    //탐색할려는 노드
	int y = startY;    //탐색할려는 노드

	nodeArr[startY][startX]._parentX = -1;
	nodeArr[startY][startX]._parentY = -1;
	nodeArr[startY][startX]._currentDistance = 0;
	nodeArr[startY][startX]._isVisited = FALSE;

	priority_queue < Pos, vector<Pos>, cmp> nodeQueue;
	
	nodeQueue.push({ startX,startY,seq++ });

	while (1)
	{
		if (nodeQueue.empty()) break;
		x = nodeQueue.top().X;
		y = nodeQueue.top().Y;
		nodeQueue.pop();

		//closed 노드일때 처리
		if (nodeArr[y][x]._isVisited) continue;

		//과정 Render
		Render(x, y);


		//노드 속성값 설정
		nodeArr[y][x]._isVisited = TRUE;

		//목적지 찾았을 때
		if (x == endX && y == endY) break;

		//노드 넣어주기
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
			
			// node 속성 설정해주기 (원래가 더빨랐다면 무시)
			auto prevDistance = nodeArr[newY][newX]._currentDistance;
			auto currentDistance = nodeArr[y][x]._currentDistance + 1;
			if (prevDistance <= currentDistance) continue;
			nodeArr[newY][newX]._currentDistance = currentDistance;
			nodeArr[newY][newX]._parentX = x;
			nodeArr[newY][newX]._parentY = y;

			nodeQueue.push({ newX, newY,seq++ });
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