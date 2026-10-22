#include <iostream>
#include <Windows.h>

#define BUF_SIZE 1024

int wmain()
{
	setlocale(LC_ALL, "Korean");

	HANDLE hPipe;
	WCHAR readDataBuf[BUF_SIZE + 1];
	LPCWSTR pipeName = L"\\\\.\\pipe\\simple_pipe";

	while (1)
	{
		hPipe = CreateFile(
			pipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			wprintf(L"Could not open pipe\n");
			return 0;
		}
		if (!WaitNamedPipe(pipeName, 20000))
		{
			wprintf(L"Could not open pipe\n");
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL isSuccess = SetNamedPipeHandleState(hPipe, &pipeMode, NULL, NULL);

	if (!isSuccess)
	{
		wprintf(L"SetNamedPipeHandleState error!\n");
		return 0;
	}

	LPCWSTR fileName = L"news.txt";
	DWORD bytesWritten = 0;

	isSuccess = WriteFile(hPipe, fileName, (wcslen(fileName) + 1) * sizeof(WCHAR), &bytesWritten, NULL);
	if (!isSuccess)
	{
		wprintf(L"WriteFile error!\n");
		return 0;
	}
	
	DWORD bytesRead = 0;
	while (1)
	{
		isSuccess = ReadFile(
			hPipe,
			readDataBuf,
			BUF_SIZE * sizeof(WCHAR),
			&bytesRead,
			NULL
		);

		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		readDataBuf[bytesRead / sizeof(WCHAR)] = 0;
		wprintf(L"%s \n", readDataBuf);
	}

	CloseHandle(hPipe);

	_getwch();
	return 0;

}