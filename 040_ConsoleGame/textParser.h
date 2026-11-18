#pragma once
#include <Windows.h>
#include <iostream>
class TextParser
{
public:
	TextParser(const char* fileName);
	~TextParser();
	//이 함수를 호출해 fileSize를 확인한다. 0이라면 생성자에서 오류가 있었던 것이다.
	int GetFileSize();
	int GetNextString(char* buf, int bufSize);
	void Init();
private:
	FILE* _fp = nullptr;
	LONG _fileSize = 0;   //실제 사용하고있는 크기(텍스트모드로 읽으면 줄어들어서)
	LONG _mallocSize = 0; //메모리할당한 크기
	char* _buffer = nullptr;
	int _index = -1;
};