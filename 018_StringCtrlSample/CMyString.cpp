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

CMyString::CMyString(CMyString&& rhs)
	:m_pszData(NULL),
	m_nlength(0)
{
	cout << "이동생성자 호출" << endl;

	m_pszData = rhs.m_pszData;
	m_nlength = rhs.m_nlength;

	rhs.m_pszData = nullptr;
	rhs.m_nlength = 0;
}

CMyString& CMyString::operator=(const CMyString& rhs)
{
	// 자기자신을 대입하는거면 해제를 해버리는구나 a = a;
	if(this != &rhs)
		SetString(rhs.GetString());


	return *this;
}

CMyString::CMyString(const char* pszParam)
	:m_pszData(NULL),
	m_nlength(0)
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
	
	//미래를 호출한다!
	OnSetString(m_pszData, m_nlength);

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

int CMyString::GetLength() const
{
	return m_nlength;
}

int CMyString::Append(const char* pszParam)
{

	if (pszParam == NULL)
		return 0;

	int nLenParam = strlen(pszParam);

	if (nLenParam == 0)
		return 0;

	if (m_pszData == NULL)
	{
		SetString(pszParam);

		return m_nlength;
	}

	int nLenCur = m_nlength;

	char* pszResult = new char[nLenCur + nLenParam + 1];

	strcpy_s(pszResult, sizeof(char) * (nLenCur + 1), m_pszData);
	strcpy_s(pszResult + nLenCur, sizeof(char) * (nLenParam + 1), pszParam);

	Release();
	m_pszData = pszResult;
	m_nlength = nLenCur + nLenParam;

	return m_nlength;
}

CMyString CMyString::operator+(const CMyString& rhs)
{
	CMyString result(GetString());
	result.Append(rhs.GetString());

	return result;
}

CMyString& CMyString::operator+=(const CMyString& rhs)
{
	this->Append(rhs.GetString());
	return *this;
}

char& CMyString::operator[](int index)
{
	return m_pszData[index];
}

char CMyString::operator[](int index) const
{
	return m_pszData[index];
}

int CMyString::operator==(const CMyString& rhs)
{
	if (m_pszData != NULL && rhs.m_pszData != NULL)
		if (strcmp(m_pszData, rhs.m_pszData) == 0)
			return 1;
	return 0;
}

int CMyString::operator!=(const CMyString& rhs)
{
	if (m_pszData != NULL && rhs.m_pszData != NULL)
		if (strcmp(m_pszData, rhs.m_pszData) == 0)
			return 0;
	return 1;
}

void CMyString::OnSetString(char* pszData, int nLength)
{

}

CMyString operator+(const char* pszParam, const CMyString& strParam)
{
	CMyString result(pszParam);
	result.Append(strParam.m_pszData);

	return result;
}
