#include <iostream>
#include <Windows.h>
#include <unordered_map>

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


	// 캐시히트 정보 출력.
	void PrintCacheHitInfo();

	//싱글톤 객체 얻기.
	static CacheHitTest& GetInstance();
private:
	static DWORD usageCount;  //캐시라인 접근시마다 1씩 증가함. LRU에 사용

	//태그정보(물리주소20bit, 마지막접근시간)
	struct TagInfo
	{
		DWORD _tag;            //태그값
		DWORD _lastAccessTime; //마지막 접근시간. : LRU에 사용
	};

	static int _numWays; //l1캐시의 way수
	static TagInfo* _tagInfo; //TagInfo [index*way + way] 형식으로 tag정보를 저장한다. 
	CacheHitTest();
	~CacheHitTest();

	//캐시히트정보를 저장하는 구조체
	struct CacheHitInfo
	{
		std::wstring _name; //이걸로해야 문자열을 key값으로 한다음 비교할수있겠는데?
		LPVOID _addr;
		DWORD _size;
		DWORD _hitCount;
		DWORD _missCount;
	};

	//캐시히트정보를 저장하는 unordered_map
	std::unordered_map<std::wstring, CacheHitInfo> _cacheHitInfoMap;

	//캐시히트여부를 저장하는 함수
	void SaveCacheHitInfo(LPCWSTR name, LPVOID addr, DWORD size, BOOL isCacheHit);
};

int CacheHitTest::_numWays = 0;
CacheHitTest::TagInfo* CacheHitTest::_tagInfo = nullptr;
DWORD CacheHitTest::usageCount = 0;

CacheHitTest::CacheHitTest()
{
	//cpu의 way수를 얻어오자.
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
	_tagInfo = (TagInfo*)malloc(sizeof(TagInfo) * _numWays * 64);

	// 0으로 초기화한다.
	// TagInfo.lastAccessTime에 0이 저장되어있다면 캐시가 비어있는 것이다
	ZeroMemory(_tagInfo, sizeof(TagInfo) * _numWays * 64);

	return;
}

CacheHitTest::~CacheHitTest()
{
	if (_tagInfo != nullptr)
		free(_tagInfo);
}

void CacheHitTest::SaveCacheHitInfo(LPCWSTR name, LPVOID addr, DWORD size, BOOL isCacheHit)
{
	//찾아보고 이미 있는 이름이라면 값을 갱신한다. 없으면 새로 추가한다.
	std::wstring str(name);
	auto iter = _cacheHitInfoMap.find(str);
	if (iter != _cacheHitInfoMap.end())
	{
		if (isCacheHit)
			iter->second._hitCount++;
		else
			iter->second._missCount++;

		return;
	}

	//이함수가 호출될 일은 없겠지.. 처음에 접근할때는 무조건 miss니까.
	if (isCacheHit)
		_cacheHitInfoMap[str] = { str, addr, size, 1, 0 };
	else
		_cacheHitInfoMap[str] = { str, addr, size, 0, 1 };
}

void CacheHitTest::CacheHit(LPVOID paramAddr, DWORD size, LPCWSTR name)
{
	if (paramAddr == nullptr || size == 0) return;


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
			if (tag == _tagInfo[index * _numWays + i]._tag)
			{
				//cache hit 일때 처리
				isCacheHit = TRUE;
				_tagInfo[index * _numWays + i]._lastAccessTime = usageCount++;
				break;
			}
		}

		if (isCacheHit == FALSE)
		{
			//cache miss 일때 처리
			//LRU방식으로 캐시라인을 넣어준다.
			//가장 오래전에 접근한 캐시라인을 찾는다.
			DWORD minAccessTime = 0xFFFFFFFF;
			DWORD minWay = 0;
			for (int i = 0; i < _numWays; i++)
			{
				if (_tagInfo[index * _numWays + i]._lastAccessTime < minAccessTime)
				{
					minAccessTime = _tagInfo[index * _numWays + i]._lastAccessTime;
					minWay = i;
				}
			}

			//교체한다.
			_tagInfo[index * _numWays + minWay]._tag = tag;
			_tagInfo[index * _numWays + minWay]._lastAccessTime = usageCount++;
		}

		// 캐시 hit/miss 정보를 저장한다.
		SaveCacheHitInfo(name, paramAddr, size, isCacheHit);

		//처리해야할 캐시라인을 다음 캐시라인으로 변경한다.
		addr += 64;
	}
}

CacheHitTest& CacheHitTest::GetInstance()
{

	static CacheHitTest instance;
	return instance;

}

void CacheHitTest::PrintCacheHitInfo()
{
	for (const auto& pair : _cacheHitInfoMap)
	{
		const CacheHitInfo& info = pair.second;
		std::wcout << L"Name: " << info._name
			<< L", Address: " << info._addr
			<< L", Size: " << info._size
			<< L", Hit Count: " << info._hitCount
			<< L", Miss Count: " << info._missCount
			<< std::endl;
	}
}

int g_c = 0;

int wmain()
{
	int a = 0;
	a++;
	CacheHitTest::GetInstance().CacheHit(&a, sizeof(int), L"a");

	a++;
	CacheHitTest::GetInstance().CacheHit(&a, sizeof(int), L"a");

	int b = 0;
	b++;
	CacheHitTest::GetInstance().CacheHit(&b, sizeof(int), L"b");

	b++;
	CacheHitTest::GetInstance().CacheHit(&b, sizeof(int), L"b");

	g_c++;
	CacheHitTest::GetInstance().CacheHit(&g_c, sizeof(int), L"g_c");

	CacheHitTest::GetInstance().PrintCacheHitInfo();
}