//named pipe 서버  Overlapped I/O 방식

#include <iostream>
#include <Windows.h>

#define BUF_SIZE 1024
int CommToClient(HANDLE);

int wmain()
{
	setlocale(LC_ALL, "Korean");

	LPCWSTR pipeName = L"\\\\.\\pipe\\simple_pipe";
	HANDLE hPipe;

	while (1)
	{
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, //OVERLAPPED 특성
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE / 2, //출력 버퍼 사이즈
			BUF_SIZE / 2, //입력 버퍼 사이즈
			20000,
			NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			wprintf(L"CreateNamedPipe failed\n");
			return -1;
		}
		
		BOOL isSuccess;
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
		//여기서 뜨는 ERROR_PIPE_CONNECTED는 클라이언트가 이미 생성된 파이프에 먼저 접속요청걸고 connectedNamedPipe()가 호출된거임.
		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}

	return -1;
}

int CommToClient(HANDLE hPipe)
{
	WCHAR fileName[MAX_PATH];
	WCHAR dataBuf[BUF_SIZE];
	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile(
		hPipe, fileName, MAX_PATH * sizeof(WCHAR), &fileNameSize, NULL);
	if (!isSuccess || fileNameSize == 0)
	{
		wprintf(L"Pipe read message error!\n");
		return -1;
	}

	FILE* filePtr;
	_wfopen_s(&filePtr, fileName, L"r");
	if (filePtr == NULL)
	{
		wprintf(L"File open fault\n");
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = CreateEvent(
		NULL,
		TRUE,
		TRUE,
		NULL
	);
	DWORD bytesWritten = 0, bytesRead = 0;
	DWORD bytesWrite = 0, bytesTransfer = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);
		bytesWrite = bytesRead;
		isSuccess = WriteFile(hPipe, dataBuf, bytesWrite, &bytesWritten, &overlappedInst);
		if (!isSuccess && GetLastError() != ERROR_IO_PENDING)
		{
			wprintf(L"Pipe write message error! \n");
			break;
		}

		//다른작업을 할 수 있는 기회

		WaitForSingleObject(overlappedInst.hEvent, INFINITE);
		GetOverlappedResult(hPipe, &overlappedInst, &bytesTransfer, FALSE);
		wprintf(L"Transferred data size : %u \n", bytesTransfer);
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}