#include <iostream>
#include <Windows.h>
#include "C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.h"

#pragma comment (lib,"C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.lib")

void Test( int a)
{
	
}

int main()
{
	WCHAR str[] = L"안녕하세요";
	std::cout << _countof(str) << std::endl;
	std::cout << sizeof(str) << std::endl;
	std::cout << wcslen(str) << std::endl;

	
}