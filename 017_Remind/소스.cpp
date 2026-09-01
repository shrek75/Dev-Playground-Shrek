#include <iostream>
#include <memory>

using namespace std;

void TestFunc1()
{
	cout << "TestFunc1()" << endl;
}

void TestFunc2()
{
	int a = 3;
	int b = 4;
	cout << a + b << endl;
	TestFunc1();
}

int main()
{	
	TestFunc2();
	
}