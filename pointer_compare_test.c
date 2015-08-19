#include <stdio.h>

int main ()
{
    int nums [] = {1,2,3};
    
    int *p1 = &nums[0];
    int *p2 = &nums[3];

    /* the value is 3, same with c++ and c++ iterator. */
    printf ("%d\n", p2-p1);   

    return 0;
}
