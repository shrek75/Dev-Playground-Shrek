#pragma once

#include "UserData.h"

class MyList
{
public:
	MyList();
	~MyList();

protected:
	void ReleaseList();
	int LoadList(const char* pszFileName);
	int SaveList(const char* pszFileName);
		UserData _head;

public:
	UserData* FindNode(const char* pszName);
	int AddNewNode(const char* pszName, const char* pszPhone);
	
	void PrintAll();

	int RemoveNode(const char* szName);

	
};

