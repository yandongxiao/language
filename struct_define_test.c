#include <stdio.h>

typedef struct _AAA AAA;

/* it should put last. */

// typedef struct _BBB {
//     AAA aaa;
// } BBB;

struct _AAA {
    int a;
    int b;
}; 

typedef struct _BBB {
    AAA aaa;
} BBB;

int main (void)
{
    BBB b;
}
