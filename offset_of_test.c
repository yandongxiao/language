#include <stdio.h>
#include <stddef.h>

typedef struct _AAA{
    int a;
    int b;
} AAA;


int
main (void)
{
    printf ("%d\n", offsetof (AAA, a));
}
