#pragma once

#include "MyNode.h"

class UserData : public MyNode
{

protected:
	char _name[32];
	char _phone[32];

	static int _userDataCounter;

public:
	UserData();
	UserData(const char* pszName, const char* pszPhone);
	~UserData();

	const char* GetName() const { return _name; }
	const char* GetPhone() const { return _phone; }

	const char* GetKey();
	void PrintNode();
	

};

