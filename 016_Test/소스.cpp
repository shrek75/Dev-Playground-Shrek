#include <iostream>
#include <Windows.h>
#include "C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.h"

#pragma comment (lib,"C:/Users/user/Desktop/MyDLL/MyFirstDLL/029_MyFirstDLL.lib")

void Test( int a)
{
	a += 1;
	int b = 0;
	int* p = &b;
	p += 3;
}

int main()
{
	
	Test(3);
	
}