#include <iostream>
#include <Windows.h>

struct MWord
{
	WCHAR eng[20];
	WCHAR kor[20];
};

class MyDictionary
{
public:
	static MWord word[100];

	void TranslateString();
};

MWord MyDictionary::word[100] =
{
	{L"I",L"나"},
	{L"AM",L"은(는)"},
	{L"A",L"하나의"},
	{L"BOY",L"소년"}
};


void MyDictionary::TranslateString()
{
	WCHAR inputString[40];
	fputws(L"문자열을 입력하세요.\n", stdout);
	fgetws(inputString, _countof(inputString), stdin);

	WCHAR transWord[20];
	//WCHAR outputString[40];
	const WCHAR* pStr = inputString;
	const WCHAR* pStart = inputString;
	while (*pStr != L'\0')
	{
		//단어를 찾았으면
		if (*pStr == L' ' || *pStr == L'\n')
		{	
			//단어만 버퍼에 복사.
			memcpy(transWord, pStart, sizeof(WCHAR) * (pStr - pStart));
			//배열의 경계 예외처리 안함.
			transWord[pStr - pStart] = L'\0';

			//단어를 대문자로 변경.
			_wcsupr_s(transWord);

			//단어 번역가능한지 확인 및 출력
			for (auto& wordSet : word)
			{
				if (wcscmp(transWord, wordSet.eng) == 0)
				{
					wprintf(L"%ls ", wordSet.kor);
					break;
				}
			}

			//다음단어 측정을 위해 포인터 옮김 : 스페이스 다음은 항상 다음단어가 온다는 가정(연속스페이스 불가)
			pStart = ++pStr;
		}
		else pStr++;
	}

}



int wmain()
{
	setlocale(LC_ALL, "Korean");

	MyDictionary m;
	m.TranslateString();


}