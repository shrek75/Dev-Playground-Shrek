#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define LEN_INPUT 11
char* solution(const char* my_string, const char* overwrite_string, int s);

int main(void) {
    
    printf("%s\n", solution("He11oWor1d", "lloWorl", 2));

    return 0;
}

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* my_string, const char* overwrite_string, int s) {



    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(1000);
    for (int i = 0; i < 1000; i++)
    {
        answer[i] = my_string[i];
        if (my_string[i] == 0) break;
    }
    for (int i = 0; i < 1000; i++)
    {
        if (overwrite_string[i] == 0) break;
        answer[s+i] = overwrite_string[i];
    }

    return answer;
}