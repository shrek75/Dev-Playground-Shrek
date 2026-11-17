#pragma once
#include <Windows.h>
#include <iostream>
class TextParser
{
public:
	TextParser(const char* fileName);
	int GetNextString(char* buf, int bufSize);
	void Init();
private:
	FILE* _fp = nullptr;
	LONG _fileSize = 0;
	char* _buffer = nullptr;
	int _index = -1;
};