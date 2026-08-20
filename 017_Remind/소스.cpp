#include <iostream>


using namespace std;

class CMyClass
{
public:
	int& _pData;
	CMyClass(int param):_pData(param)
	{
		cout << _pData << endl;

	}
	void Print()
	{
		cout << _pData << endl;
	}
};

void Foo()
{
	cout << "안녕하세용가리어카세트리오" << endl;
}

int wmain()
{

	int test = 10;
	CMyClass* a = new CMyClass(test);

	Foo();
	a->_pData = 20;
	a->Print();
	
	return 0;

}