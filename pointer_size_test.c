#include <stdio.h>

int 
main ()
{
    char *v = NULL;

    printf ("%p\n", v+1);           /* 1 */

    printf ("%p\n", ((void*)v)+1);  /* 1 */

    printf ("%p\n", ((double*)v)+1);  /* 8 */

    printf ("%p\n", &v);

    /* (&v) will be considered as (char**), the size of char* is 4 */
    printf ("%p\n", (&v)+1);    /* plus 4 */

    return 0;
}
