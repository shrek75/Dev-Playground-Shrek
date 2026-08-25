#pragma once
class CMyString
{
private:

	//문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
	char* m_pszData;
	
	//저장된 문자열의 길이
	int m_nlength;

public:
	
	CMyString();
	~CMyString();
	CMyString(const CMyString& rhs);
	CMyString(CMyString&& rhs);
	CMyString& operator=(const CMyString& rhs);
	CMyString(const char* pszParam);
	operator char* ()const;

	int SetString(const char* pszParam);
	const char* GetString() const;
	void Release();

	int GetLength() const;

	int Append(const char* pszParam);

	CMyString operator +(const CMyString& rhs);
	CMyString& operator +=(const CMyString& rhs);

	char& operator[](int index);
	char operator[](int index) const;

	int operator==(const CMyString& rhs);
	int operator!=(const CMyString& rhs);

	virtual void OnSetString(char* pszData, int nLength);
	friend CMyString operator+(const char* pszParam, const CMyString& strParam);
};

