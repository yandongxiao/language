#include <stdio.h>

#define AAA 100 // If you define AAA again, and it must be same with up one.*/

#define da(num)    \
    10;   \
    do{   \
        1000;\
        num=10; \
    }while(0);   \
    100 
    
int test() {
	printf("%d\n", AAA);
}

int main() {
	test();
    int a;
    int b=1;
    b = da(a);      /* if the first statement in da are surrounded in {}, will happen error. Or it equal b = num = 10, if num=10 is the first statement. */
    100;
    printf("b == %d\n", b);
}
