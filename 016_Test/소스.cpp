#include <iostream>
#include <Windows.h>
using namespace std;

int wmain() {
	
	unsigned char a, b, c;
	a = 0b10101010;
	b = 0b00110011;
	c = 0b10011001;

	printf("%02x\n", a);
	printf("%02x\n", b);
	printf("%02x\n", c);

	printf("%02x\n", b^c);
	printf("%02x\n", a^c);
	printf("%02x\n", a ^ b);


	
}