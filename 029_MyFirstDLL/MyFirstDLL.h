#pragma once

#ifdef _WIN32
#ifdef MY029MYFIRSTDLL_EXPORTS
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

    MYDLL_API void MyQuickSort(int* arr, int count);

#ifdef __cplusplus
}
#endif
