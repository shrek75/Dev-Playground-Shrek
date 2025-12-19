
#include <iostream>

int Func(char p[])
{
    printf("%s\n", p);
    return 0;
}
int main()
{
    char arr[3][10] = { "Hello","MyNameis","TaeUk" };

    Func(arr[2]);
    
}

