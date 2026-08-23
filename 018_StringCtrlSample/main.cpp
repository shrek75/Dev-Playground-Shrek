#include "CMyString.h"
#include <iostream>

using namespace std;

void TestFunc(const CMyString& param)
{
	cout << param.GetString() << endl;
}


int main()
{
	CMyString strData;
	strData.SetString("Hello");
	cout << strData.GetString() << endl;
}