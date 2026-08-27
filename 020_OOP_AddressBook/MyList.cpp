#include "MyList.h"
#include <conio.h>
#include <string>

#define DATA_FILE_NAME "MyAddress.dat"

MyList::MyList()
{
	LoadList(DATA_FILE_NAME);
}

MyList::~MyList()
{
	SaveList(DATA_FILE_NAME);
	ReleaseList();
}

void MyList::ReleaseList()
{
	UserData* pDelete;
	UserData* pNext = _head._next;
	while (pNext != nullptr)
	{
		pDelete = pNext;
		pNext = pNext->_next;

		delete pDelete;
	}
	_head._next = nullptr;
}

int MyList::LoadList(const char* pszFileName)
{
	FILE* fp = NULL;
	UserData user;

	fopen_s(&fp, pszFileName, "rb");

	if (fp == NULL)
		return 0;

	ReleaseList();

	while (fread(&user, sizeof(UserData), 1, fp))
	{
		AddNewNode(user._name, user._phone);
	}

	fclose(fp);

	return 0;
}

int MyList::SaveList(const char* pszFileName)
{
	FILE* fp = NULL;
	UserData* pTmp = _head._next;

	fopen_s(&fp, pszFileName, "wb");

	if (fp == NULL)
	{
		puts("ERROR: 리스트 파일을 쓰기 모드로 열지 못했습니다.");
		_getch();

		return 0;
	}

	while (pTmp != NULL)
	{
		if (fwrite(pTmp, sizeof(UserData), 1, fp) != 1)
			printf("ERROR: %s에 대한 정보를 저장하는데 실패했습니다.", pTmp->_name);

		pTmp = pTmp->_next;
	}

	fclose(fp);

	return 1;
}

UserData* MyList::FindNode(const char* pszName)
{
	UserData* pTmp = _head._next;
	while (pTmp != nullptr)
	{
		if (strcmp(pTmp->GetName(), pszName) == 0)
			break;
		pTmp = pTmp->_next;
	}
	return pTmp;
}

int MyList::AddNewNode(const char* pszName, const char* pszPhone)
{
	if (FindNode(pszName) != nullptr) return 0;

	UserData* pUser = new UserData();
	strcpy_s(pUser->_name, sizeof(pUser->_name), pszName);
	strcpy_s(pUser->_phone, sizeof(pUser->_phone), pszPhone);

	pUser->_next = _head._next;
	_head._next = pUser;

	return 1;
}

void MyList::PrintAll()
{
	UserData* pData = _head._next;
	while (pData != NULL)
	{
		printf("[%p] %s\t%s [%p]\n",
			pData,
			pData->GetName(), pData->GetPhone(),
			pData->GetNext());
		pData = pData->_next;
	}

}

int MyList::RemoveNode(const char* szName)
{
	UserData* pTmp = _head._next;
	UserData* prev = &_head;
	while (pTmp != nullptr)
	{
		if (strcmp(pTmp->GetName(), szName) == 0)
		{
			prev->_next = pTmp->_next;
			delete pTmp;
			return 1;
		}
		prev = pTmp;
		pTmp = pTmp->_next;
	}
	
	return 0;

}
