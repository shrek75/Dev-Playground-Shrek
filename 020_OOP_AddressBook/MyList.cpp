#include "MyList.h"
#include <conio.h>
#include <string>
#include "UserData.h"

#define DATA_FILE_NAME "MyAddress.dat"

MyList::MyList(MyNode* head)
{
	_head = head;
	LoadList(DATA_FILE_NAME);
}

MyList::~MyList()
{
	SaveList(DATA_FILE_NAME);
	ReleaseList();
}

void MyList::ReleaseList()
{
	MyNode* pDelete;
	MyNode* pNext = _head->_next;
	while (pNext != nullptr)
	{
		pDelete = pNext;
		pNext = pNext->_next;

		delete pDelete;
	}
	_head->_next = nullptr;
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
		AddNewNode(new UserData(user.GetName(),user.GetPhone()));
	}

	fclose(fp);

	return 0;
}

int MyList::SaveList(const char* pszFileName)
{
	FILE* fp = NULL;
	MyNode* pTmp = _head->_next;

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
			printf("ERROR: %s에 대한 정보를 저장하는데 실패했습니다.", pTmp->GetKey());

		pTmp = pTmp->_next;
	}

	fclose(fp);

	return 1;
}

MyNode* MyList::FindNode(const char* _key)
{
	MyNode* pTmp = _head->_next;
	while (pTmp != nullptr)
	{
		if (strcmp(pTmp->GetKey(), _key) == 0)
			break;
		pTmp = pTmp->_next;
	}
	return pTmp;
}

int MyList::AddNewNode(MyNode* node)
{
	if (FindNode(node->GetKey()) != nullptr) return 0;

	node->_next = _head->_next;
	_head->_next = node;

	return 1;
}

void MyList::PrintAll()
{
	MyNode* pData = _head->_next;
	while (pData != NULL)
	{
		pData->PrintNode();
		pData = pData->_next;
	}

}

int MyList::RemoveNode(const char* key)
{
	MyNode* pTmp = _head->_next;
	MyNode* prev = _head;
	while (pTmp != nullptr)
	{
		if (strcmp(pTmp->GetKey(), key) == 0)
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
