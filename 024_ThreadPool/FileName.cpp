#include <iostream>
#include <Windows.h>

#define WORK_MAX 10000
#define THREAD_MAX 50

typedef void (*WORK) (void);

DWORD AddWorkToPool(WORK work);
WORK GetWorkFromPool(void);
DWORD MakeThreadToPool(DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);

struct WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
};

struct ThreadPool
{
	//Work를 등록하기 위한 배열
	WORK workList[WORK_MAX];
	
	// Thread 정보와 각 Thread별 event 오브젝트
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];

	//Work에 대한 정보
	DWORD idxOfCurrentWork; // 대기 1순위 Work Index
	DWORD idxOfLastAddedWork; //마지막 추가 Work Index + 1

	// Number of Thread;
	DWORD threadIdx;       //Pool에 존재하는 Thread의 개수
};

ThreadPool threadPool;

//*******************************************
// Mutex 관련 함수들
// threadPool에 대한 접근을 보호하기 위해 정의
//*******************************************
static HANDLE mutex = NULL;

void InitMutex(void)
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex(void)
{
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex(void)
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);
	if (ret == WAIT_FAILED)
		printf("Error Occur!\n");
}

void ReleaseMutex()
{
	BOOL ret = ReleaseMutex(mutex);
	if(ret == 0)
		printf("Error Occur!\n");
}

//*******************************************
// Thread Pool에 Work를 등록시키기 위한 함수
//*******************************************
DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();
	if (threadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		printf("AddWorkToPool() fail!\n");
		return NULL;
		//왜 Mutex반환안하지?
	}

	//Work 등록
	threadPool.workList[threadPool.idxOfLastAddedWork++] = work;

	// Work 등록후, 대기중인 쓰레드들을 모두 깨워 일을 시작하도록 함
	// 모두 깨울 필요가 없으므로 정교함이 떨어지는 부분이다.
	for (DWORD i = 0; i < threadPool.threadIdx; i++)
		SetEvent(threadPool.workerEventList[i]);

	ReleaseMutex();
	return 1;
}

//*******************************************
// Thread에서 Work를 가져올 때 호출되는 함수
// threadPool에 대한 접근을 보호하기 위해 정의
//*******************************************
WORK GetWorkFromPool()
{
	WORK work = NULL;

	AcquireMutex();
	
	//현재 처리해야할 Work가 존재하지 않는다면
	if (!(threadPool.idxOfCurrentWork < threadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = threadPool.workList[threadPool.idxOfCurrentWork++];
	ReleaseMutex();

	return work;
}

//*******************************************
// Thread Pool 생성
// 전달되는 인자값에 따라 Thread생성
//*******************************************
DWORD MakeThreadToPool(DWORD numOfThread)
{
	InitMutex();
	//왜 WORK_MAX인지 이해가안가는데.. 아무리생각해도 THREAD_MAX인데
	DWORD capacity = THREAD_MAX - (threadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;
	
	for (DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;

		threadPool.workerEventList[threadPool.threadIdx]
			= CreateEvent(NULL, FALSE, FALSE, NULL);

		hThread = CreateThread(
			NULL, 0,
			(LPTHREAD_START_ROUTINE)WorkerThreadFunction,
			(LPVOID)threadPool.threadIdx,
			0, &idThread
		);

		threadPool.workerThreadList[threadPool.threadIdx].hThread = hThread;
		threadPool.workerThreadList[threadPool.threadIdx].idThread = idThread;

		threadPool.threadIdx++;
	}

	//생성된 쓰레드의 수를 반환한다.
	return numOfThread;
}

// 전달되어야 할 대상
void WorkerThreadFunction(LPVOID pParam)
{
	WORK workFunction;
	HANDLE event = threadPool.workerEventList[(DWORD)pParam];

	while (1)
	{
		workFunction = GetWorkFromPool();
		if (workFunction == NULL)
		{
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}

// Simple Work Function
void TestFunction()
{
	//i는 static이므로 둘 이상의 쓰레드에 의해 동시접근 가능하다
	// 따라서 동기화가 필요하지만 동기화를 생략한다
	static int i = 0;
	i++;

	printf("Good Test --%d : Processing thread: %d--\n\n", i, GetCurrentThreadId());
}

int main()
{
	MakeThreadToPool(2);

	for (int i = 0; i < 10000; i++)
	{
		AddWorkToPool(TestFunction);
	}

	Sleep(50000);
	return 0;
}