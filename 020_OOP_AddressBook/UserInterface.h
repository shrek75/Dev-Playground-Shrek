#pragma once

#include "MyList.h"

class UserInterface
{
public:
	UserInterface(MyList& list);
	~UserInterface();

protected:
	MyList &_list;

public:
	
	int PrintUI();

	void Add();
	void Search();
	void Remove();
	int PrintAll();

	int Run();

};

