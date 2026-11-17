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
	_fileSize = ftell(_fp);
	_buffer = (char *)malloc(_fileSize);
	if (_buffer == nullptr)
	{
		_fileSize = 0;
		return;
	}

	fread_s(_buffer, _fileSize, sizeof(char), _fileSize, _fp);

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
	while (_index < _fileSize)
	{
		//내부버퍼의 index값을 1증가한다.
		_index++;
		
		//문장의 끝을 찾았으면 break
		if (_buffer[_index] == '\n' || _buffer[_index] == EOF)
			break;
		
		//복사될 버퍼의 크기를 초과해도 break
		if (dstIndex >= bufSize)
			break;

		//복사.
		buf[dstIndex] = _buffer[_index];
		dstIndex++;
	}

	//복사한 문자열의 끝에는 NULL문자를 넣어준다.
	if (dstIndex > 0)
		buf[dstIndex - 1] = '\0';

	return dstIndex - 1;
}

void TextParser::Init()
{
	_index = 0;
}
