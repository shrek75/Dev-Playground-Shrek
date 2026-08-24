#include <iostream>

using namespace std;

class CMyData
{
public:
	CMyData()
	{
		cout << "CMyData()" << endl;
	}

	virtual ~CMyData() {}
	virtual void TestFunc1() {}
	virtual void TestFunc2() {}

	void TestFunc3() {}
};

class CMyDataEx : public CMyData
{
public:
	CMyDataEx()
	{
		cout << "CMyDataEx()" << endl;

	}

	virtual ~CMyDataEx() {}
//	virtual void TestFunc1() {}
	virtual void TestFunc2()
	{
		cout << "TestFunc2()" << endl;
	}
};

int main()
{
	const int dieNum = 4;
	int& what = const_cast<int&>(dieNum);
	what = 5;
	cout << dieNum << endl;

	CMyData* pData = new CMyDataEx;
	pData->TestFunc2();
	delete pData;

	pData->TestFunc3();

	return 0;
}