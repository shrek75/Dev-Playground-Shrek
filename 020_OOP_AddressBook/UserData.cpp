#include "UserData.h"
#include <memory>

UserData::UserData()
	:_next(nullptr),
	_name{0},
	_phone{0}
{
	// memset(_name,0,sizeof(_name));
	// memset(_phone, 0, sizeof(_phone));

}

UserData::~UserData()
{
}
