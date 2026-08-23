#include <iostream>


using namespace std;

class CMyClass
{
public:
	CMyClass()
	{
		cout << "CMyClass()" << endl;
	
		pData = new int(10);
	}

	

	~CMyClass()
	{
		cout << "~CMyClass()" << endl;

		//delete pData;
	}

	CMyClass& operator=(const CMyClass& rhs)
	{
		cout << "operator=(const CMyClass&)" << endl;
		*this->pData = *rhs.pData;
		
		return *this;
	}

	CMyClass& operator=(CMyClass&& rhs)
	{
		cout << "operator=(const CMyClass&&)" << endl;
		this->pData = rhs.pData;
		rhs.pData = nullptr;

		return *this;
	}

	CMyClass(const CMyClass& rhs)
	{
		cout << "CMyClass(const CMyClass &)" << endl;
		
		pData = new int;
		*pData = *rhs.pData;
	}
	CMyClass(CMyClass&& rhs)
	{
		cout << "CMyClass(const CMyClass &&)" << endl;

		pData = rhs.pData;
		rhs.pData = nullptr;
	}

	explicit CMyClass(int param)
	{
		cout << "CMyClass(int)" << endl;
		pData = new int(param);
	}

	explicit operator int(void)
	{
		return 1;
	}

	void Print()
	{
		cout << *pData << endl;
	}

	void TestFunc3() const
	{
		int a = 3;
		a++;
	}

private:
	int* pData = nullptr;
};

void TestFunc(const CMyClass& param)
{
	cout << "TestFunc()" << endl;
}

CMyClass TestFunc2(CMyClass param)
{
	cout << "TestFunc2() begin" << endl;
	
	cout << "TestFunc2() end" << endl;

	return param;
}



int wmain()
{
	cout << "시작" << endl;

	//CMyClass c;
	TestFunc2(30);

	cout << "끝" << endl;

}