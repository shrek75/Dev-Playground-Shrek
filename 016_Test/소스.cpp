#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (!hTimer)
	{
		printf("CreateWaitableTimer failed (%d) \n", GetLastError());
		return -1;
	}
	
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	while (1)
	{
		WaitForSingleObject(hTimer, INFINITE);
		printf("Timer was signaled\n");
		MessageBeep(MB_ICONEXCLAMATION);
	}
	return 0;
}