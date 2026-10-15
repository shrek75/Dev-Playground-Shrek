#include <iostream>
#include <Windows.h>
using namespace std;


int wmain(int argc, WCHAR* argv[]) {
	DWORD val1, val2;
	val1 = _wtoi(argv[1]);
	val2 = _wtoi(argv[2]);
	
	fputws(argv[0], stdout);
	fputws(L"\n", stdout);
	wprintf(L"%d + %d = %d", val1, val2, val1 + val2);

	_getwch();
	return 0;
	
	
}