#pragma once
#include <Windows.h>

struct PROFILE_SAMPLE
{
	int _dataNum;       //샘플의 사용여부
	WCHAR _name[64];  //샘플의 이름

	INT64 _min[3];    //최소값
	INT64 _max[3];    //최대값
	INT64 _totalTime; //총합산시간(평균내는용도)
	INT64 _data[10000]; //데이터는 call 10000번까지만 저장. (중간값 얻어보고 싶어서)
	// 8byte * 10000개 * 30sample => 2.4MB
	//삽입은 빠르게. 중간값 계산은 저장할때 1번만하면 되니까 배열쓰면될듯.

	INT64 _callTimes; //call 횟수
};

class Profiler
{
public:
	//생성자 소멸자로 프로파일 자동 시작,종료되게. 
	Profiler(const WCHAR* name);
	~Profiler();
	static void Reset();
	static void ProfileDataOutText(const WCHAR* fileName);
	static LARGE_INTEGER GetQPF();
private:
	//인스턴스가 사라져도 프로파일 데이터는 남아있어야 하니 static으로 구현.
	static PROFILE_SAMPLE _profiles[50];

	WCHAR _name[64];          //프로파일 샘플 이름
	LARGE_INTEGER _startTime; //프로파일 샘플의 시작시간.
};