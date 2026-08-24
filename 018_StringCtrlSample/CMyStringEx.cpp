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
