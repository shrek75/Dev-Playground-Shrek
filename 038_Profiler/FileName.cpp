#include "profiler.h"
#include <iostream>


Profiler::Profiler(const WCHAR* name)
{
	_startTime.QuadPart = 0;
	wcscpy_s(_name, name);
	QueryPerformanceCounter(&_startTime);
}

Profiler::~Profiler()
{
	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&endTime);

	//프로파일 배열에서 샘플이름 검색
	//없으면 새로 만들어야함.

	//데이터 저장하기
}

void Profiler::Reset()
{
	
}

void Profiler::ProfileDataOutText(const WCHAR* fileName)
{
	
}

LARGE_INTEGER Profiler::GetQPF()
{
	//람다 신기하네.. 
	//static으로 초기화 한번만 하기.
	static LARGE_INTEGER _freq = [] {
		LARGE_INTEGER n;
		QueryPerformanceFrequency(&n);
		return n;
		}();
	return _freq;
}

int main()
{
	return 0;
}