#pragma once

#ifdef _WIN32
#ifdef CACHEHITCHECK_EXPORTS
#define MYDLL_API __declspec(dllexport)   // dll 빌드할 때
#else
#define MYDLL_API __declspec(dllimport)   // dll 가져다 쓸 때
#endif
#else
#define MYDLL_API
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//이 곳에 함수를 선언한다.
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
		MYDLL_API void CacheHit(LPVOID paramAddr, DWORD size, LPCWSTR name);


		// 캐시히트 정보 출력.
		MYDLL_API void PrintCacheHitInfo();

		//싱글톤 객체 얻기.
		MYDLL_API static CacheHitTest& GetInstance();
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
		MYDLL_API CacheHitTest();
		MYDLL_API ~CacheHitTest();

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
		MYDLL_API void SaveCacheHitInfo(LPCWSTR name, LPVOID addr, DWORD size, BOOL isCacheHit);
	};

#ifdef __cplusplus
}
#endif