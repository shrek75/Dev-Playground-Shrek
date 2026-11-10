#pragma once

// [PROFILE]로 사용하면된다. [PROFILER]가 정의되어있으면 제대로 작동한다.
#ifdef PROFILER
#define PROFILE(name) Profiler p(name)
#else
#define PROFILE(name)
#endif


#ifdef _WIN32
#ifdef PROFILER_EXPORTS //프로젝트 매크로기본정의 된것.
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
#include <Windows.h>

#define PROFILE_NUMS 50 //프로파일 샘플 개수

	struct PROFILE_SAMPLE
	{
		WCHAR _name[64] = { 0 };  //샘플의 이름

		UINT64 _min[3] = { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF };    //최소값
		UINT64 _max[3] = { 0,0,0 };    //최대값
		UINT64 _totalTime = 0; //총합산시간(평균내는용도)
		UINT64 _data[10000] = { 0 }; //데이터는 call 10000번까지만 저장. (중간값 얻어보고 싶어서)
		// 8byte * 10000개 * 30sample => 2.4MB
		//삽입은 빠르게. 중간값 계산은 저장할때 1번만하면 되니까 배열쓰면될듯.

		UINT64 _callTimes = 0; //call 횟수, 0이면 해당샘플을 사용하지 않는것으로 본다.
	};

	//생성자에 프로파일샘플 이름을 전달해서 사용한다.
	class Profiler
	{
	public:
		//생성자 소멸자로 프로파일 자동 시작,종료되게. 
		MYDLL_API Profiler(const WCHAR* name);
		MYDLL_API ~Profiler();
		MYDLL_API static void Reset();
		MYDLL_API static void ProfileDataOutText(const WCHAR* fileName);
	private:
		MYDLL_API static LARGE_INTEGER GetQPF();

		//인스턴스가 사라져도 프로파일 데이터는 남아있어야 하니 static으로 구현.
		inline static PROFILE_SAMPLE _profiles[PROFILE_NUMS];

		WCHAR _name[64];          //프로파일 샘플 이름
		LARGE_INTEGER _startTime; //프로파일 샘플의 시작시간.
	};

#ifdef __cplusplus
}
#endif