#include <stdio.h>

typedef enum _AAA {
    RES_TYPE_NUM,
    RES_TYPE_STR = RES_TYPE_NUM     /* normally, you should not do this. */
} AAA;

int
main ()
{
    AAA a = -1;     /* assign var @a to an integer. */
}
