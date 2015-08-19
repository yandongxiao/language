#include <stdio.h>

int a = 10;

static const struct {   /* struct with no name. */
    int a;
    int b;

}
array[] = {
    {0,0},
    {1,1},
    {2,2},
    {3,3}

};

int main()
{
    double a []= {};
    printf("%d\n", sizeof(a) / sizeof (a[0]));  /* 0 */
    printf("%d\n", sizeof (a[0]));  /* 4 */

    /* list initialization, can not be used as normal assign.*/
    char *str [] = {"dsa", NULL}; 
//    str = {"ddsa", NULL}; /* error */
}
