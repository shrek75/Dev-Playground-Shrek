#include "CMyStringEx.h"
#include <cstring>
int CMyStringEx::Find(const char* pszParam)
{
	if (GetString() == NULL || pszParam == NULL)
		return -1;

	const char* ret = strstr(GetString(), pszParam);
	if (ret == NULL) return -1;

	return ret - GetString();

}

void CMyStringEx::OnSetString(char* pszData, int nLength)
{
	if (strcmp(pszData, "멍멍이아들") == 0)
		strcpy_s(pszData, sizeof(char) * (nLength + 1), "*착한아들*");
}

//CMyStringEx::CMyStringEx(const char* pszParam)
//	:CMyString(pszParam)
//{
//}

//int CMyStringEx::SetString(const char* pszParam)
//{
//	if (pszParam == NULL) return -1;
//
//	if (strcmp(pszParam, "멍멍이아들") == 0)
//		CMyString::SetString("착한사람");
//	else
//		CMyString::SetString(pszParam);
//
//
//	return 0;
//}
