#include <iostream>
#include "C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.h"
//#include "C:\Users\user\Desktop\MyDLL\MyFirstDLL\MyFirst.h"

#pragma comment (lib,"C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.lib")

int main()
{
	int arr[10] = { 10,9,8,7,6,5,4,3,2,1 };
	MyQuickSort(arr, 10);

	for (int n : arr)
	{
		printf("%d ", n);
	}

	getchar();

}