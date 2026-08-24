#include "CMyStringEx.h"
#include <iostream>

using namespace std;





int main()
{
	CMyStringEx strTest;
	strTest.SetString("I am a boy.");
	cout << strTest << endl;

	int nIndex = strTest.Find("am");
	cout << "Index : " << nIndex << endl;


	return 0;

}