#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
////////////////////////////////////////////
// 주소록이 저장될 데이터 파일
#define DATA_FILE_NAME "Address.dat"

////////////////////////////////////////////
void ReleaseList();



////////////////////////////////////////////
typedef struct _USERDATA
{
	char szName[32];  // 이름
	char szPhone[32]; // 전화번호
	
	struct _USERDATA* pNext;
} USERDATA;

USERDATA g_Head = { 0 };

////////////////////////////////////////////
// 리스트에서 이름으로 특정 노트 검색하는 함수
USERDATA* FindNode(char* pszName)
{
	USERDATA* pTmp = g_Head.pNext;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->szName, pszName) == 0)
			break;
		pTmp = pTmp->pNext;
	}
	return pTmp;
}

////////////////////////////////////////////
int AddNewNode(char* szName, char* szPhone)
{
	if (FindNode(szName) != NULL)
		return 0;

	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewNode, 0, sizeof(USERDATA));

	strcpy_s(pNewNode->szName, sizeof(pNewNode->szName), szName);
	strcpy_s(pNewNode->szPhone, sizeof(pNewNode->szPhone), szPhone);

	pNewNode->pNext = g_Head.pNext;
	g_Head.pNext = pNewNode;

	return 1;
}

///////////////////////////////////////////
// 이름을 입력받아 리스트에 추가하는 함수
void Add()
{
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };
	printf("Input name :");
	gets_s(szName, sizeof(szName));
	getchar();


	printf("Input phone number : ");
	gets_s(szPhone, sizeof(szPhone));
	getchar();


	AddNewNode(szName, szPhone);
}

////////////////////////////////////////
// 특정 노드를 검색하는 함수
void Search()
{
	char szName[32] = { 0 };
	USERDATA* pNode = NULL;

	printf("Input name :");
	gets_s(szName, sizeof(szName));
	getchar();


	pNode = FindNode(szName);
	if (pNode != NULL)
	{
		printf("[%p] %s\t%s [%p]\n",
			pNode,
			pNode->szName, pNode->szPhone,
			pNode->pNext);
		_getch();

	}
	else
	{
		puts("ERROR: 데이터를 찾을 수 없습니다.");
		_getch();

	}
}

/// <summary>
/// 리스트에 들어있는 모든 데이터를 화면에 출력하는 함수
/// </summary>
void PrintAll()
{
	USERDATA* pData = g_Head.pNext;
	while (pData != NULL)
	{
		printf("[%p] %s\t%s [%p]\n",
			pData,
			pData->szName, pData->szPhone,
			pData->pNext);
		pData = pData->pNext;
	}

	_getch();
}

/// <summary>
/// 특정노드를 검색하고 삭제하는 함수
/// </summary>
/// <param name="pszName">이름</param>
/// <returns>성공시 1, 실패시 0 반환</returns>
int RemoveNode(char* pszName)
{
	USERDATA* pTmp = g_Head.pNext;
	USERDATA* pTmp_prev = &g_Head;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->szName, pszName) == 0)
			break;
		pTmp_prev = pTmp;
		pTmp = pTmp->pNext;
	}
	if (pTmp == NULL) return 0;

	pTmp_prev->pNext = pTmp->pNext;
	
	free(pTmp);

	return 1;
}

/// <summary>
/// 이름을 입력받아 자료를 검색하고 삭제하는 함수
/// </summary>
void Remove()
{
	char szName[32] = { 0 };

	printf("Input Name: ");
	gets_s(szName, sizeof(szName));
	getchar();


	RemoveNode(szName);
}

/// <summary>
/// 메뉴를 출력하는 UI함수
/// </summary>
/// <returns>선택한 메뉴의 값</returns>
int PrintUI()
{
	int nInput = 0;

	system("cls");

	printf("[1] Add\t [2] Search\t [3] Print all\t [4] Remove\t [0] Exit\n");

	scanf_s("%d", &nInput);
	getchar();

	return nInput;
}

/// <summary>
/// 데이터 파일에서 노드들을 읽어와 리스트를 완성하는 함수
/// </summary>
/// <param name="pszFileName">파일이름</param>
/// <returns></returns>
int LoadList(char* pszFileName)
{
	FILE* fp = NULL;
	USERDATA user = { 0 };

	fopen_s(&fp, pszFileName, "rb");

	if (fp == NULL)
		return 0;

	ReleaseList();

	while (fread(&user, sizeof(USERDATA), 1, fp))
	{
		AddNewNode(user.szName, user.szPhone);
	}

	fclose(fp);

	return 0;
}

/// <summary>
/// 리스트 형태로 존재하는 정보를 파일에 저장하는 함수
/// </summary>
/// <param name="pszFileName">파일이름</param>
/// <returns></returns>
int SaveList(char* pszFileName)
{
	FILE* fp = NULL;
	USERDATA* pTmp = g_Head.pNext;

	fopen_s(&fp, pszFileName, "wb");

	if (fp == NULL)
	{
		puts("ERROR: 리스트 파일을 쓰기 모드로 열지 못했습니다.");
		_getch();

		return 0;
	}

	while (pTmp != NULL)
	{
		if (fwrite(pTmp, sizeof(USERDATA), 1, fp) != 1)
			printf("ERROR: %s에 대한 정보를 저장하는데 실패했습니다.", pTmp->szName);

		pTmp = pTmp->pNext;
	}

	fclose(fp);

	return 1;

}

/// <summary>
/// 리스트의 모든 데이터를 삭제하는 함수
/// </summary>
void ReleaseList()
{
	USERDATA* pDelete = &g_Head;
	USERDATA* pNext = g_Head.pNext;

	while (pNext != NULL)
	{
		pDelete = pNext;
		pNext = pDelete->pNext;

		free(pDelete);
	}

	memset(&g_Head, 0, sizeof(USERDATA));
}

void main()
{
	int nMenu = 0;
	LoadList(DATA_FILE_NAME);

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

	SaveList(DATA_FILE_NAME);
	ReleaseList();
}