#pragma once
class UserData
{
	friend class MyList;

protected:
	char _name[32];
	char _phone[32];

	UserData* _next;

public:
	UserData();
	~UserData();

	const char* GetName() const { return _name; }
	const char* GetPhone() const { return _phone; }
	const UserData* GetNext() const { return _next; }

};

