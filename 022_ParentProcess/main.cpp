#include <iostream>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int wmain(int argc, WCHAR* argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi1, pi2;
	si.cb = sizeof(si);

	WCHAR t[DIR_LEN];
	GetCurrentDirectory(DIR_LEN, t);

	wprintf(L"Current directory: %s\n", t);

	WCHAR command1[] = L"023_ChildProcess.exe 1 5";
	WCHAR command2[] = L"023_ChildProcess.exe 6 10";

	CreateProcess(NULL, command1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi1);
	CreateProcess(NULL, command2, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi2);

	
	int sum1, sum2, sum3 = 0;
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	

	GetExitCodeProcess(pi1.hProcess, (LPDWORD)&sum1);
	GetExitCodeProcess(pi2.hProcess, (LPDWORD)&sum2);


	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	sum3 = sum1 + sum2;

	wprintf(L"Sum of 1 to 10 is: %d\n", sum3);

}