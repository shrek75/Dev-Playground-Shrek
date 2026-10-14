#include <iostream>
using namespace std;

static int test;

class M
{
public:
	static int _count;
	int data;
	M()
	{
		data = 0;
		_count = 1000;
	}
};
int M::_count = 1;

void TestFunc()
{
	M myclass;
	cout << myclass._count << endl;
}

int main() {
	
	TestFunc();
	cout << M::_count << endl;

	//g_x = 4;
	
}