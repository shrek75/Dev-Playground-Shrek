#include <iostream>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int wmain(int argc, WCHAR* argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.lpTitle = const_cast<LPWSTR>(L"I am a boy");
	WCHAR command[] = L"AdderProcess.exe 33 66";
	WCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);
	fputws(cDir, stdout);
	fputws(L"\n", stdout);

	SetCurrentDirectory(L"C:\\WinSystem");

	GetCurrentDirectory(DIR_LEN, cDir);
	fputws(cDir, stdout);
	fputws(L"\n", stdout);

	state = CreateProcess(
		NULL,
		command,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi
	);

	if(state)
		fputws(L"Process created successfully\n", stdout);
	else
		fputws(L"Process creation failed\n", stdout);

	// wprintf(L"%d", GetLastError());
	return 0;


}