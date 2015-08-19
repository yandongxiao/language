#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 20;

    a = atoi("d345g");
    printf("%d\n", a);  /* 0 */

    a = atoi("345g");
    printf("%d\n", a);  /* 345 */

    a = atoi("345889889898989");
    printf("0x%x\n", a);    /*the max value of a is 0x7FFFFFFF*/

    a = atoi("-345889889898989");
    printf("0x%x\n", a);    /*the min value of a is 0x80000000*/
}
