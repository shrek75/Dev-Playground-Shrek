#include <iostream>
#include <Windows.h>
#include <process.h>

#define THREAD_NUMS 6

int total = 0;

void IncreaseCount()
{
	total++;
}

unsigned int __stdcall ThreadProc(LPVOID lpParam)
{
	for (int i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}
	return 0;
}

int main()
{
	HANDLE hThreads[THREAD_NUMS];
	DWORD threadIDs[THREAD_NUMS];

	for (int i = 0; i < THREAD_NUMS; i++)
	{
		hThreads[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned int*) & threadIDs[i]);
		if (hThreads[i] == NULL)
		{
			std::cout << "쓰레드 생성실패" << std::endl;
			return 0;
		}
	}

	for (int i = 0; i < THREAD_NUMS; i++)
	{
		ResumeThread(hThreads[i]);
	}

	WaitForMultipleObjects(THREAD_NUMS, hThreads, TRUE, INFINITE);
	
	for (int i = 0; i < THREAD_NUMS; i++)
	{
		CloseHandle(hThreads[i]);
	}


	std::cout << "토탈 : " << total << std::endl;

	return 0;

}