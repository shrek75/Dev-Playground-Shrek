#include "CMyStringEx.h"
#include <iostream>

using namespace std;





int main()
{
	CMyString b("World"), c;
	c = "Hello" + b;
	cout << c << endl;
}