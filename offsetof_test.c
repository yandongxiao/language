#include <stdio.h>

typedef struct st {
    int a;
    int b;
} st_t;

int main ()
{
/* use &, you can avoid to access the contents of the filed. similar lea */
#define OFFSETOF(type, field)   (int)&(((type *)0)->field)

    printf ("%d\n", OFFSETOF(st_t, a));
    printf ("%d\n", OFFSETOF(st_t, b));
}
