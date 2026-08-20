#include <iostream>


using namespace std;

template <typename T>
T Foo(T x, T y)
{
	return x + y;
}

int wmain()
{
	cout << Foo(1.2, 1.3) << endl;
	cout << Foo(1, 2) << endl;


	
	return 0;

}