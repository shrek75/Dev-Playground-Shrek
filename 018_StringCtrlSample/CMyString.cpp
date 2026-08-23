#include "CMyString.h"
#include <iostream>

using namespace std;

CMyString::CMyString()
	:m_pszData(NULL),
	m_nlength(0)
{
	
}

CMyString::~CMyString()
{
	Release();
}

CMyString::CMyString(const CMyString& rhs)
	:m_pszData(NULL),
	m_nlength(0)
{
	SetString(rhs.GetString());
}

CMyString& CMyString::operator=(const CMyString& rhs)
{
	// 자기자신을 대입하는거면 해제를 해버리는구나 a = a;
	if(this != &rhs)
		SetString(rhs.GetString());


	return *this;
}

CMyString::CMyString(const char* pszParam)
{
	SetString(pszParam);
}

CMyString::operator char* () const
{
	return m_pszData;
}

int CMyString::SetString(const char* pszParam)
{
	Release();

	//인자 유효성 체크
	if (pszParam == NULL) return -1;

	//복사할 문자 길이 체크
	m_nlength = strlen(pszParam);
	if (m_nlength == 0) return 0;

	m_pszData = new char[m_nlength + 1];
	strcpy_s(m_pszData, m_nlength+1, pszParam);
	return m_nlength;
}

const char* CMyString::GetString() const
{
	return m_pszData;
}

void CMyString::Release()
{
	if (m_pszData != NULL)
		delete[] m_pszData;
	m_pszData = NULL;
	m_nlength = 0;
	return;
}
