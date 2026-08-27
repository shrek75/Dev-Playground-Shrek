#include "UserData.h"
#include <memory>

UserData::UserData()
	:_name{0},
	_phone{0}
{
	// memset(_name,0,sizeof(_name));
	// memset(_phone, 0, sizeof(_phone));

}

UserData::UserData(const char* pszName,const char* pszPhone)
	:_name{ 0 },
	_phone{ 0 }
{
	memcpy(_name, pszName, sizeof(_name));
	memcpy(_phone, pszPhone, sizeof(_phone));
}

UserData::~UserData()
{
}

const char* UserData::GetKey()
{
	return _name;
}

void UserData::PrintNode()
{
	printf("%s\t%s\n",
		_name, _phone);
}
