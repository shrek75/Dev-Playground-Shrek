#include "CMyString.h"
#include <iostream>

using namespace std;

CMyString::CMyString()
	:m_pszData(NULL)
{
	m_nlength = 0;
}

CMyString::~CMyString()
{
}

int CMyString::SetString(const char* pszParam)
{
	//인자 유효성 체크
	if (pszParam == NULL) return -1;

	//이미 할당되어있는 메모리 있는지 체크
	if (m_pszData != NULL) Release();

	//복사할 문자 길이 체크
	m_nlength = strlen(pszParam);
	if (m_nlength == 0) return 0;

	m_pszData = new char[m_nlength + 1];
	strcpy_s(m_pszData, m_nlength+1, pszParam);
	return m_nlength;
}

const char* CMyString::GetString()
{
	return m_pszData;
}

void CMyString::Release()
{
	if (m_nlength <= 0) return;
	delete[] m_pszData;
	return;
}
