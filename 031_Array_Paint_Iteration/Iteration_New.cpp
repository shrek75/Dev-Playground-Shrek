#include <iostream>
#include <Windows.h>
#include <stack>
#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 20

long long int a = 4;

char Original[SCREEN_HEIGHT][SCREEN_WIDTH] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '0', '0', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', '0', '0', ' ' },
	{ ' ', ' ', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', ' ', ' ', '0', '0', '0', ' ' },
	{ ' ', '0', '0', '0', '0', '0', ' ', ' ', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', ' ' },
	{ ' ', '0', '0', '0', '0', ' ', ' ', ' ', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', ' ' },
	{ ' ', '0', '0', '0', ' ', '0', ' ', ' ', '0', '0', '0', ' ', ' ', '0', '0', '0', '0', '0', '0', ' ' },
	{ ' ', '0', '0', ' ', ' ', '0', ' ', '0', '0', '0', ' ', '0', '0', ' ', '0', '0', '0', '0', ' ', ' ' },
	{ ' ', '0', '0', ' ', '0', '0', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', '0', '0', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '0', ' ', ' ', '0', ' ', '0', '0', '0', '0', '0', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
};


void PrintMap();
void Paint(int index);
char** memArr[5000000];
int myStack[1000][2]; //지역변수로 넣으니까 사아알짝 더느린데?..


int main()
{
	clock_t start, finish;

	//메모리 복사가 오래걸리는 거 같아서 미리해둘게.
	for (int i = 0; i < 5000000; i++)
	{
		memArr[i] = (char**)malloc(sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);
		memcpy(memArr[i], Original, sizeof(char) * SCREEN_HEIGHT * SCREEN_WIDTH);
	}

	start = clock();
	for (int i = 0; i < 5000000; i++)
	{
		Paint(i);
	}
	finish = clock();

	printf("%d\n", finish - start);
}

void Paint(int index)
{
	myStack[0][0] = 10;
	myStack[0][1] = 5;
	int myStackCount = 0;

	while (1)
	{
		if (-1 == myStackCount) return;

		int posX = myStack[myStackCount][0];
		int posY = myStack[myStackCount][1];
		myStackCount--;

		//맵 벗어나는지 확인
		if (!(posX >= 0 && posX < SCREEN_WIDTH && posY >= 0 && posY < SCREEN_HEIGHT))
		{
			continue;
		}
		//자기 지점 ' ' 인지 '0' 인지 'X' 인지 확인
		if (memArr[index][posY][posX] == ' ' || memArr[index][posY][posX] == 'X')
		{
			continue;
		}

		//자기 지점 도착.
		memArr[index][posY][posX] = 'X';

		//Render
		//PrintMap();

		//북남서동 
		myStackCount++;
		myStack[myStackCount][0] = posX;
		myStack[myStackCount][1] = posY - 1;

		myStackCount++;
		myStack[myStackCount][0] = posX;
		myStack[myStackCount][1] = posY + 1;

		myStackCount++;
		myStack[myStackCount][0] = posX - 1;
		myStack[myStackCount][1] = posY;

		myStackCount++;
		myStack[myStackCount][0] = posX + 1;
		myStack[myStackCount][1] = posY;
	}
}

void PrintMap()
{
	system("cls");

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
			putchar(Original[y][x]);
		putchar('\n');
	}
	Sleep(100);
}