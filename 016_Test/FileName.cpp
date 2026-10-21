#include <iostream>
#include <Windows.h>

int TestFunc(int t)
{
	int a = t;
	a++;

	return 1;
}

int main()
{
	TestFunc(5);
	printf("hi");
	int m = 0;

	do {
		if (m == 0)
			break;
	printf("정상\n");
	return 0;
	} while (0);



	ERROR_MESSAGE:
	printf("ERROR\n");

	return 1;



}