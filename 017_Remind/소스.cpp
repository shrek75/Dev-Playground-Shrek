#include <stdio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	UINT pageSize = sysInfo.dwPageSize;

	HANDLE hHeap = HeapCreate(
		HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);

	int* p = (int *)HeapAlloc(hHeap, 0, sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		p[i] = i;

	HeapFree(hHeap, 0, p);

	HeapDestroy(hHeap);
	
}