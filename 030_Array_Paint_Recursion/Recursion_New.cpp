#include <iostream>
#include <Windows.h>

#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 20

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
void Paint(int posX, int posY, int index);
char** memArr[5000000];

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
		Paint(10, 5 , i);
	}
	finish = clock();

	printf("%d\n", finish - start);
}

void Paint(int posX, int posY, int index)
{
	//반복문에서 이거 해줘서 얘도 공평하게 넣어줫음.
	int x = posX;
	int y = posY;

	//맵 벗어나는지 확인
	if (!(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT))
		return;

	//자기 지점 ' ' 인지 '0' 인지 'X' 인지 확인
	if (memArr[index][y][x] == ' ' || memArr[index][y][x] == 'X') return;

	//자기 지점 도착.
	memArr[index][y][x] = 'X';

	//Render
	//PrintMap();

	//동서남북 탐방
	Paint(x + 1, y ,index);
	Paint(x - 1, y, index);
	Paint(x, y + 1, index);
	Paint(x, y - 1, index);
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