#include "CMyString.h"
#include <iostream>

using namespace std;

int main()
{
	CMyString strData;
	strData.SetString("Hello");
	cout << strData.GetString() << endl;
}