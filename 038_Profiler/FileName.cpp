#include "profiler.h"
#include <iostream>
#include <algorithm>
#define PROFILER

Profiler::Profiler(const WCHAR* name)
	:_startTime{}, _name{}
{
#ifdef PROFILER
	wcscpy_s(_name, name);
	QueryPerformanceCounter(&_startTime);
#endif
}

Profiler::~Profiler()
{
#ifdef PROFILER
	//종료시간 기록
	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&endTime);
	INT64 elapsedTime = endTime.QuadPart - _startTime.QuadPart;

	//프로파일 배열에서 샘플이름으로 검색
	for (int i = 0; i < PROFILE_NUMS; i++)
	{
		//이름이 다르다면 continue.
		if (_profiles[i]._callTimes != 0)
		{
			if (wcscmp(_profiles[i]._name, _name) != 0) continue;
		}
		//해당이름이 없다면 빈곳에 새로 저장해주기.
		else
			wcscpy_s(_profiles[i]._name, _name);


		//1만회 까지만 데이터저장 (중간값 얻어보고 싶음)
		if (_profiles[i]._callTimes < 10000)
			_profiles[i]._data[_profiles[i]._callTimes] = elapsedTime;

		// 총합시간 합산
		_profiles[i]._callTimes++;
		_profiles[i]._totalTime += elapsedTime;

		// 최소값/최대값 계산
		UINT64 targetTime = elapsedTime;
		for (int x = 0; x < 3; x++)
		{
			if (targetTime < _profiles[i]._min[x])
			{
				UINT64 temp = _profiles[i]._min[x];
				_profiles[i]._min[x] = targetTime;
				targetTime = temp;
			}
		}
		targetTime = elapsedTime;
		for (int x = 0; x < 3; x++)
		{
			if (targetTime > _profiles[i]._max[x])
			{
				UINT64 temp = _profiles[i]._max[x];
				_profiles[i]._max[x] = targetTime;
				targetTime = temp;
			}
		}
		//저장했으니 break
		break;
	}
#endif
}

void Profiler::Reset()
{
#ifdef PROFILER
	for (int i = 0; i < PROFILE_NUMS; i++)
	{
		if (_profiles[i]._callTimes != 0) break;
		
		_profiles[i]._callTimes = 0;
		_profiles[i]._totalTime = 0;
		_profiles[i]._min[0] = 0xFFFFFFFFFFFFFFFF;
		_profiles[i]._min[1] = 0xFFFFFFFFFFFFFFFF;
		_profiles[i]._min[2] = 0xFFFFFFFFFFFFFFFF;
		_profiles[i]._max[0] = 0;
		_profiles[i]._max[1] = 0;
		_profiles[i]._max[2] = 0;
	}
#endif
}

void Profiler::ProfileDataOutText(const WCHAR* fileName)
{
#ifdef PROFILER

	//파일열기
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		wprintf(L"file save error : %d\n", GetLastError());
		return;
	}
	
	//맨윗줄 출력
	WCHAR buf[100];
	swprintf_s(buf, L"\t\t\t MIN\t\t MAX\t\t AVG\t\t Median\t\t Call\n");
	WriteFile(hFile, buf, ((DWORD)wcslen(buf) + 1) * sizeof(WCHAR), nullptr, nullptr);

	//데이터 출력
	for (int i = 0; i < PROFILE_NUMS; i++)
	{
		if (_profiles[i]._callTimes == 0) break;

		//MicroSecond단위로 파일에 저장한다.
		double TransMicroSecond = GetQPF().QuadPart / (double)1000000;

		//중간값을 얻기위해 데이터를 정렬한다.
		//최대 1만개까지 데이터를 저장하므로, 1만회 이상호출했다면 count를 1만으로 보정해서 정렬한다.
		UINT64 medianDataCount = _profiles[i]._callTimes > 10000 ? 10000 : _profiles[i]._callTimes;
		std::qsort(_profiles[i]._data, medianDataCount, sizeof(UINT64),
			[](const void* a, const void* b) -> int 
			{
				return *((UINT64*)a) > *((UINT64*)b);
			});
		UINT64 median = _profiles[i]._data[medianDataCount / 2];

		//데이터를 순서와 형식에 맞게 buf에 담는다.
		swprintf_s(buf, L"[%16s]\t %0.1lf\t %0.1lf\t %0.1lf\t %0.1lf\t\t %lld\n",
			_profiles[i]._name,
			_profiles[i]._min[0] / TransMicroSecond,
			_profiles[i]._max[0] / TransMicroSecond,
			_profiles[i]._totalTime / TransMicroSecond / _profiles[i]._callTimes,
			median / TransMicroSecond,
			_profiles[i]._callTimes
			);

		//출력
		WriteFile(hFile, buf, ((DWORD)wcslen(buf) + 1) * sizeof(WCHAR), nullptr, nullptr);
	}

	CloseHandle(hFile);
#endif
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
	{
		Profiler p(L"TestFunc");
		for (int i = 0; i < 10000000; i++);
	}
	Profiler::ProfileDataOutText(L"TestProfile.txt");
	return 0;
}