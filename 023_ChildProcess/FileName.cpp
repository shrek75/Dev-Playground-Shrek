#include <iostream>
#include <Windows.h>

int wmain(int argc, WCHAR* argv[])
{
	int start = _wtoi(argv[1]);
	int end = _wtoi(argv[2]);

	int sum = 0;
	for (int i = start; i <= end; i++)
	{
		sum += i;
	}
	return sum;
}