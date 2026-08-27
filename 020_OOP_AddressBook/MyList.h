#pragma once

#include "MyNode.h"

class MyList
{
public:
	MyList(MyNode* head);
	~MyList();

protected:
	void ReleaseList();
	int LoadList(const char* pszFileName);
	int SaveList(const char* pszFileName);
	MyNode* _head;

public:
	MyNode* FindNode(const char* key);
	int AddNewNode(MyNode* node);
	
	void PrintAll();

	int RemoveNode(const char* key);

	
};

