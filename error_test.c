/* make sure the macro defined when compile, or create an error. */


#ifndef __cplusplus
# error 亲，您当前使用的不是C++编译器噢！
#endif

#include <stdio.h>
int main()
{
    printf("Hello,World!");
    return 0;
}
