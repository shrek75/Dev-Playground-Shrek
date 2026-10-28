#include <iostream>
#include <Windows.h>
#include <thread>
void Render(int* arr, int count, int pivotIndex, int leftIndex, int rightIndex);

void MyQuickSort(int* arr, int count)
{
	//피벗을 설정한다. (제일왼쪽)
	//피벗 바로 다음것을 left로 선정, 오른쪽끝을 right로 선정.
	//right를 먼저 움직이면서 피벗보다 작은걸찾고, left를 움직이면서 피벗보다 큰걸 찾는다. right부터 움직이는이유가 마지막에 하나 무조건바꿔야해서
	// 둘다 찾으면 swap하고 겹치면. 겹친부분 피벗이랑 교환.
	// 피벗기준으로 정렬됐으니 다시 quicksort
	// return하는 조건은.. count가 1일때
	if (count <= 1) return;
	int pivotIdx = 0;
	int leftIdx = 1;
	int rightIdx = count - 1;

	static int renderCount = count;
	static int* renderArr = arr;

	while (1)
	{
		//right를 움직이면서 pivot보다 작은 놈 찾기.
		while (leftIdx != rightIdx)
		{
			Render(renderArr, renderCount, pivotIdx, leftIdx, rightIdx);
			if (arr[rightIdx] < arr[pivotIdx]) break;
			rightIdx--;
		}
		//left를 움직이면서 pivot보다 큰놈 찾기
		while (leftIdx != rightIdx)
		{
			Render(renderArr, renderCount, pivotIdx, leftIdx, rightIdx);
			if (arr[leftIdx] > arr[pivotIdx]) break;
			leftIdx++;
		}

		// left/right 겹쳤다면 종료
		if (leftIdx == rightIdx) break;

		// left<->right swap
		int temp = arr[leftIdx];
		arr[leftIdx] = arr[rightIdx];
		arr[rightIdx] = temp;
		Render(renderArr, renderCount, pivotIdx, leftIdx, rightIdx);

	}

	// 겹쳤을 때 pivot이 더크면 swap하기.
	if (arr[pivotIdx] > arr[leftIdx])
	{
		int temp = arr[pivotIdx];
		arr[pivotIdx] = arr[leftIdx];
		arr[leftIdx] = temp;

		pivotIdx = leftIdx;
		Render(renderArr, renderCount, pivotIdx, leftIdx, rightIdx);

	}

	//피벗을 기준으로 좌우가 정렬 되었으니, 구간을 분할해서 다시 퀵소트.
	MyQuickSort(arr, pivotIdx);
	MyQuickSort(arr + pivotIdx + 1, count - pivotIdx - 1);
}

void Render(int* arr, int count, int pivotIndex, int leftIndex, int rightIndex)
{
	Sleep(1000);
	system("cls");
	for (int i = 0; i < count; i++)
	{
		if (i == pivotIndex) printf("  P");
		else printf("   ");
	}
	printf("\n");

	for (int i = 0; i < count; i++)
	{
		printf("%3d", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < count; i++)
	{
		if (i == leftIndex) printf("  L");
		else if (i == rightIndex) printf("  R");
		else printf("   ");
	}
	printf("\n");
}


int Test()
{
	int a = 5;
	a += 5;
	return a;
}


UINT WINAPI ThreadProc(LPVOID param)
{
	return 1;
}

//#pragma pack(push,1)
struct MyStruct
{
	char a : 4;
	char b : 4;
};
//#pragma pack(pop)


int main()
{
	MyStruct m;
	m.a = 0x0F;
	m.b = 0x0E;
	printf("%d\n", sizeof(m));
	
}