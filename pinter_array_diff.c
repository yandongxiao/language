#include <stdio.h>

int main()
{
    char (*aa) [10];
    char *bb [10];

    char t1[10];
    char t2[12];

    printf("%d\n", sizeof(aa));     /* aa is a ponter. 4 */
    printf("%d\n", sizeof(bb));     /* 40 */

    aa = &t1;       /* aa = &t2; will occur a warnning. */
    
    bb[0] = t1;     /* legal */
    bb[1] = t2;
}
