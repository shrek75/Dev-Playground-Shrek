#include <iostream>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

char string[100];
HANDLE hEvent;

int main()
{
	HANDLE hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL
	);

	if (hEvent == NULL)
	{
		fputs("Event object creation error\n", stdout);
		return -1;
	}
	
	hThread = (HANDLE)_beginthreadex(
		NULL, 0,
		OutputThreadFunction,
		NULL, 0,
		(unsigned int*)&dwThreadID
	);

	if (hThread == 0)
	{
		fputs("Thread creation error \n", stdout);
		return -1;
	}

	fputs("Insert String : ",stdout);
	fgets(string, 30, stdin);

	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hEvent);
}

unsigned int __stdcall OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);

	fputs("Output string : ", stdout);
	fputs(string, stdout);

	return 0;
}
