#include <iostream>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

char string[100];
HANDLE hEvent;
HANDLE hMutex;

int main()
{
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL
	);
	hMutex = CreateMutex(
		NULL,
		FALSE,
		NULL
	);

	if (hEvent == NULL)
	{
		fputs("Event object creation error\n", stdout);
		return -1;
	}
	if (hMutex == NULL)
	{
		fputs("Mutex creation error\n", stdout);
		return -1;
	}
	hThread[0] = (HANDLE)_beginthreadex(
		NULL, 0,
		OutputThreadFunction,
		NULL, 0,
		(unsigned int*)&dwThreadID[0]
	);

	hThread[1] = (HANDLE)_beginthreadex(
		NULL, 0,
		CountThreadFunction, NULL,
		0, (unsigned int*)&dwThreadID[1]
	);

	if (hThread[0] == 0 || hThread[1] == 0)
	{
		fputs("Thread creation error \n", stdout);
		return -1;
	}

	fputs("Insert String : ",stdout);
	fgets(string, 30, stdin);

	SetEvent(hEvent);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hEvent);
	CloseHandle(hMutex);
}

unsigned int __stdcall OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	WaitForSingleObject(hMutex, INFINITE);

	fputs("Output string : ", stdout);
	fputs(string, stdout);

	ReleaseMutex(hMutex);
	return 0;
}

unsigned int __stdcall CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	WaitForSingleObject(hMutex, INFINITE);

	printf("output string length : %d \n", strlen(string)-1);
	
	ReleaseMutex(hMutex);


	return 0;
}
