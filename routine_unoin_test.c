#include <stdio.h>

typedef union UN_s {
    int a;
    int b;
}UN;

int main() 
{
    UN t;
    t.a = 10;
    printf("union.b = %d\n", t.b);
}
