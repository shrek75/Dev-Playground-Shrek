#include "UserInterface.h"
#include <iostream>
#include <conio.h>

UserInterface::UserInterface(MyList& list)
    :_list(list)
{
}

UserInterface::~UserInterface()
{
}

int UserInterface::PrintUI()
{
	int nInput = 0;

	system("cls");

	printf("[1] Add\t [2] Search\t [3] Print all\t [4] Remove\t [0] Exit\n");

	scanf_s("%d", &nInput);
	getchar();

	return nInput;
}

void UserInterface::Add()
{
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };
	printf("Input name :");
	gets_s(szName, sizeof(szName));
	getchar();


	printf("Input phone number : ");
	gets_s(szPhone, sizeof(szPhone));
	getchar();


	_list.AddNewNode(szName, szPhone);
}

void UserInterface::Search()
{
	char szName[32] = { 0 };
	UserData* pNode = NULL;

	printf("Input name :");
	gets_s(szName, sizeof(szName));
	getchar();


	pNode = _list.FindNode(szName);
	if (pNode != NULL)
	{
		printf("[%p] %s\t%s [%p]\n",
			pNode,
			pNode->GetName(), pNode->GetPhone(),
			pNode->GetNext());
		_getch();

	}
	else
	{
		puts("ERROR: 데이터를 찾을 수 없습니다.");
		_getch();

	}
}

void UserInterface::Remove()
{
	char szName[32] = { 0 };

	printf("Input Name: ");
	gets_s(szName, sizeof(szName));
	getchar();


	_list.RemoveNode(szName);
}

int UserInterface::PrintAll()
{
	_list.PrintAll();
	_getch();
	return 0;
}

int UserInterface::Run()
{
	int nMenu = 0;

	//메인 이벤트 반복문
	while ((nMenu = PrintUI()) != 0)
	{
		switch (nMenu)
		{
		case 1: //Add
			Add();
			break;

		case 2: //Search
			Search();
			break;

		case 3: //Print all
			PrintAll();
			break;

		case 4: //Remove
			Remove();
			break;
		}
	}

	return nMenu;
}
