#include <iostream>
#include <Windows.h>
#define MAX_PAGE     10 //할당할 최대 페이지 개수

using namespace std;

int* nextPageAddr;
DWORD pageCnt = 0;
DWORD pageSize;
int pageFaultExceptionFilter(DWORD);

int main()
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;

	GetSystemInfo(&sSysInfo);
	pageSize = sSysInfo.dwPageSize;

	// MAX_PAGE 개수 만큼 Page RESERVE!!
	baseAddr = VirtualAlloc(
		NULL,				 // 임의주소할당
		pageSize * MAX_PAGE, // 예약메모리크기
		MEM_RESERVE,         // RESERVE
		PAGE_NOACCESS);
	if (baseAddr == NULL)
		cout << "VirtualAlloc Reserve Failed" << endl;

	lpPtr = static_cast<int*>(baseAddr); //배열의 시작 번지와 같은 의미 부여
	nextPageAddr = lpPtr;

	// page fault 발생 시 예외 발생
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++)
	{
		__try
		{
			lpPtr[i] = i;
		}
		__except (pageFaultExceptionFilter(GetExceptionCode()))
		{
			ExitProcess(GetLastError()); // 예외처리 문제발생시 종료!
		}
	}


	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++)
		cout << lpPtr[i] << " ";

	BOOL isSuccess = VirtualFree(
		baseAddr,
		0,
		MEM_RELEASE);
	if (isSuccess)
		cout << "Release Successed!" << endl;
	else
		cout << "Release Failed!" << endl;
	
}

int pageFaultExceptionFilter(DWORD exptCode)
{
	// 예외의 원인이 'pageFault'가 아니라면
	if (exptCode != EXCEPTION_ACCESS_VIOLATION)
	{
		cout << "Exception Code : " << exptCode << endl;
		return EXCEPTION_EXECUTE_HANDLER;
	}
	cout << "Exception is a Page Fault!" << endl;

	if (pageCnt >= MAX_PAGE)
	{
		cout << "Exception : out of pages" << endl;
		return EXCEPTION_EXECUTE_HANDLER;
	}

	LPVOID lpvResult =
		VirtualAlloc(
			nextPageAddr,
			pageSize,
			MEM_COMMIT,
			PAGE_READWRITE
		);

	if (lpvResult == NULL)
	{
		cout << "VirtualAlloc Reserve Failed" << endl;
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		cout << "Allocation another page" << endl;
	}

	pageCnt++;
	nextPageAddr += (pageSize / sizeof(int));

	//page fault가 발생한 지점부터 실행을 계속
	return EXCEPTION_CONTINUE_EXECUTION;
}
