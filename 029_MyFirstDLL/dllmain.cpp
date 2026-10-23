#include "pch.h"
#include "MyFirstDLL.h"
#include <iostream>

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

	while (1)
	{
		//right를 움직이면서 pivot보다 작은 놈 찾기.
		while (leftIdx != rightIdx)
		{
			if (arr[rightIdx] < arr[pivotIdx]) break;
			rightIdx--;
		}
		//left를 움직이면서 pivot보다 큰놈 찾기
		while (leftIdx != rightIdx)
		{
			if (arr[leftIdx] > arr[pivotIdx]) break;
			leftIdx++;
		}

		// left/right 겹쳤다면 종료
		if (leftIdx == rightIdx) break;

		// left<->right swap
		int temp = arr[leftIdx];
		arr[leftIdx] = arr[rightIdx];
		arr[rightIdx] = temp;
	}

	// 겹쳤을 때 pivot이 더크면 swap하기.
	if (arr[pivotIdx] > arr[leftIdx])
	{
		int temp = arr[pivotIdx];
		arr[pivotIdx] = arr[leftIdx];
		arr[leftIdx] = temp;

		pivotIdx = leftIdx;
	}

	//피벗을 기준으로 좌우가 정렬 되었으니, 구간을 분할해서 다시 퀵소트.
	MyQuickSort(arr, pivotIdx);
	MyQuickSort(arr + pivotIdx + 1, count - pivotIdx - 1);
}