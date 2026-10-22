#include <iostream>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Korean");
	WCHAR fileName[] = L"data.txt";
	WCHAR fileData[] = L"Just test String~";
	
	HANDLE hFile = CreateFile(
		fileName, GENERIC_WRITE, FILE_SHARE_WRITE,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		wprintf(L"FILE CREATION FAULT");
		return -1;
	}
	
	DWORD numOfByteWritten = 0;
	WriteFile(
		hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	
	wprintf(L"Written data size : %u\n", numOfByteWritten);
	CloseHandle(hFile);

	return 0;
}