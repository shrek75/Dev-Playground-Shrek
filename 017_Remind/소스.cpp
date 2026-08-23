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

	void TestFunc() const
	{
		mu_int++;
		//my_int++;
	}

	void TestFunc2(const int& param)
	{
		int& myConstCast = const_cast<int&>(param);
		myConstCast++;
		
	}

	int my_int = 5;
	mutable int mu_int = 5;
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

	int t(50);
	a->TestFunc2(t);
	cout << t;
	return 0;

}