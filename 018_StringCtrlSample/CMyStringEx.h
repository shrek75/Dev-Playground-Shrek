#pragma once
#include "CMyString.h"
class CMyStringEx :
    public CMyString
{
public:

    using CMyString::CMyString;
    int Find(const char* pszParam);
    //int SetString(const char* pszParam);

    //CMyStringEx(const char* pszParam);

    void OnSetString(char* pszData, int nLength);
};

