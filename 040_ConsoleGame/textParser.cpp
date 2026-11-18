#include "textParser.h"

TextParser::TextParser(const char* fileName)
{
	if (fopen_s(&_fp, fileName, "r") != 0)
	{
		//파일열기 실패시
		_fp = nullptr;
		return;
	}

	//파일 사이즈 얻어서 그만큼 메모리 할당
	fseek(_fp, 0, SEEK_END);
	_mallocSize = ftell(_fp);
	fseek(_fp, 0, SEEK_SET);
	_buffer = (char *)malloc(_mallocSize);
	if (_buffer == nullptr)
	{
		_mallocSize = 0;
		return;
	}

	_fileSize = fread_s(_buffer, _mallocSize, sizeof(char), _mallocSize, _fp);
	fclose(_fp);
}

//한 문장을 가져오는 함수.
//복사한 문자열의 길이를 반환한다.
int TextParser::GetNextString(char* buf, int bufSize)
{
	//복사될 버퍼의 크기가 0보다 작으면 복사하지 않는다.
	if (bufSize <= 0) return 0;

	//복사될 버퍼의 Index
	int dstIndex = 0;

	//현재 내부버퍼의 _index가  파일크기를 넘지않을 때까지만 작동한다.
	while (_index + 1 < _fileSize)
	{
		//내부버퍼의 index값을 1증가한다.
		_index++;
		
		//문장의 끝을 찾았으면 break
		//이거 EOF를 체크해야하나
		if (_buffer[_index] == '\n' || _buffer[_index] == EOF)
			break;
		
		//복사될 버퍼의 크기를 초과해도 break (NULL문자 넣어줘야함)
		if (dstIndex >= bufSize - 1)
			break;

		//복사.
		buf[dstIndex] = _buffer[_index];
		dstIndex++;
	}

	//복사한 문자열의 끝에는 NULL문자를 넣어준다.
	if (dstIndex > 0)
		buf[dstIndex] = '\0';

	return dstIndex;
}

void TextParser::Init()
{
	_index = 0;
}


TextParser::~TextParser()
{
	if (_buffer != nullptr)
		free(_buffer);
}

int TextParser::GetFileSize()
{
	return _fileSize;
}
