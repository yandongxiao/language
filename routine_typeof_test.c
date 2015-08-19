#include<stdio.h>

int main()
{
    int a = 0;
    typeof(a) *pa;
    pa = &a;
    (*pa)++;

    printf("a == %d\n", a);

}
