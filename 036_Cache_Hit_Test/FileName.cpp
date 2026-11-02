#include <iostream>
#include <Windows.h>


class CacheHitTest
{
public:
	/// <summary>
	/// 캐시히트의 여부를 판단한다.
	/// (하나의 코어에서 내 쓰레드만 수행된다고 가정.) (32bit시스템 가정)
	/// </summary>
	/// <param name="paramAddr">인스턴스의 주소</param>
	/// <param name="size">인스턴스의 크기</param>
	/// <param name="name">이름</param>
	void CacheHit(LPVOID paramAddr, DWORD size, LPCWSTR name);

	static CacheHitTest& GetInstance()
	{
		static CacheHitTest instance;
		return instance;
	}


private:
	static int _numWays; //way수
	static DWORD** _tagInfo; //DWORD [index][way] 형식으로 tag정보를 저장한다. 
	CacheHitTest();
	~CacheHitTest()
	{
		if (_tagInfo != nullptr)
			free(_tagInfo);

	}
};

int CacheHitTest::_numWays = 0;
static DWORD** _tagInfo = nullptr;

CacheHitTest::CacheHitTest()
{
	//처음에 필요한 크기를 얻어온다음, 그만큼 메모리를 할당하는 구조의 API래.
	DWORD pLength = 0;
	GetLogicalProcessorInformationEx(RelationCache, nullptr, &pLength);
	auto pInfo = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)malloc(pLength);
	if (pInfo == nullptr)
	{
		printf("malloc failed\n");
		return;
	}

	BOOL success = GetLogicalProcessorInformationEx(RelationCache, pInfo, &pLength);
	if (!success)
	{
		printf("GetLogicalProcessorInformationEx failed with error %d\n", GetLastError());
		return;
	}

	_numWays = (int)pInfo->Cache.Associativity;
	free(pInfo);

	//DWORD [index][way] 형식으로 tag정보를 저장한다.
	_tagInfo = (DWORD**)malloc(sizeof(DWORD) * _numWays * 64);

	// 0으로 초기화한다.
	// 0이 저장되어있다면 캐시가 비어있는 것으로 가정한다.
	// 원래 의미는 Page #0 으로 봐야겠지만 0번째 페이지 우리가 못쓰니까 상관없어 보인다.
	ZeroMemory(_tagInfo, sizeof(DWORD) * _numWays * 64);

	return;
}

void CacheHitTest::CacheHit(LPVOID paramAddr, DWORD size, LPCWSTR name)
{
	//캐시 hit 여부 판단

	// 몇개의 캐시라인이 저장되어야할지 판단부터 해야한다.
	// 첫번째 데이터의 주소(시작주소) 와 마지막 데이터의주소(끝주소) 가 필요하다.
	// 시작주소와 끝주소의 offset(6bit)를 날린다.
	// 그러면 tag(20bit) + index(6bit) 정보만 남게된다.
	// 필요한 캐시라인 수 == 끝주소(tag+index) - 시작주소(tag+index) + 1.

	DWORD startAddr = (DWORD)paramAddr;   // 첫 데이터의 주소
	DWORD endAddr = startAddr + size - 1; // 마지막 데이터의 주소

	//처리하고 있는 캐시라인. (마스킹안해도 문제없지만 개념적으로 깔끔하게^^)
	DWORD addr = startAddr & 0xFFFFFFC0;

	//총 캐시라인 수 : 반복문 몇번돌릴지 정하기 위함.
	DWORD numCacheLines;
	DWORD startAddrTagOffset = startAddr >> 6;
	DWORD endAddrTagOffset = endAddr >> 6;
	numCacheLines = endAddrTagOffset - startAddrTagOffset + 1;
	
	
	//캐시라인 수 만큼 캐시 hit 여부 판단.
	for (DWORD i = 0; i < numCacheLines; i++)
	{
		// index 구하기
		// index를 하위6bit 자리로 옮기고, 상위26bit를 마스킹으로 없앴다.
		DWORD index = (addr >> 6) & 0x0000003F;
		
		// tag 구하기
		DWORD tag = addr >> 12;

		// 캐시hit 여부 판단
		// 우리 CPU는 동일한index를 가진 캐시라인을 way개수만큼 저장할 수 있으므로, way수만큼 반복하여 순차적으로 탐색한다.
		BOOL isCacheHit = FALSE;
		for (int i = 0; i < _numWays; i++)
		{
			if (tag == _tagInfo[index][_numWays])
			{
				isCacheHit = TRUE;
				//cache hit 일때 처리
				
				break;
			}
		}

		if (isCacheHit == FALSE)
		{
			//cache miss 일때 처리

		}

		//처리해야할 캐시라인을 다음 캐시라인으로 변경한다.
		addr += 64;
	}

	
	// 캐시 miss 라면 새로 캐시라인을 가져와야하니 tag정보 저장.
	// 캐시라인이 꽉 찼다면, LRU방식(Least Recently Used)으로 교체한다. 
	 
	//캐시 hit 정보 저장


}
int wmain()
{
	CacheHitTest::GetInstance().CacheHit(nullptr, 0, L"test");
}