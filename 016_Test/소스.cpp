#include <iostream>
#include <Windows.h>
#include <locale.h>
using namespace std;

#define MAX_THREADS (1024 * 10)

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		wprintf(L"Thread num : %d \n", threadNum);
		Sleep(5000);
	}

	return 0;
}

DWORD cntOfThreads = 0;

int wmain() {
	setlocale(LC_ALL, "Korean");
	
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	while(1)
	{
		hThread[cntOfThreads] = 
			CreateThread(NULL, 1024 * 512 , ThreadProc, (LPVOID)cntOfThreads, 0, &dwThreadId[cntOfThreads]);

		if (hThread[cntOfThreads] == NULL)
		{
			wprintf(L"maximum thread count : %d \n", cntOfThreads);
			break;
		}

		cntOfThreads++;
	}

	for (DWORD i = 0; i < cntOfThreads; i++)
	{
		CloseHandle(hThread[i]);
	}

	return 0;
}