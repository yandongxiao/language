#include <stdio.h>

#define STRING_LIST {"HOST", NULL}

void test (char * list[])   /* equal char ** */
{
    printf("%d\n", sizeof(list));   /* 4 */
}

int 
main()
{
    char *list[] = STRING_LIST;     /* list will faile. */
//    char *list2[];    /* error: give the array size */

//    list2 = STRING_LIST;    /* wrong */
    printf("%d\n", sizeof(list));   /* 8 */

    test(list);
}

