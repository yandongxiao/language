#include <stdio.h>
#include <stdlib.h>

/*
 * you can pass a paramter( which is a macro ) to macro A.
 * you can pass the MACRO a "None", like XXX('s', SPACE, )
 */

#define SPACE(s) \
    isspace(s)  \

#define XXX(s, COND, non)    \
    printf("s=%s, COND=%s, non='%s'\n", #s, #COND, #non);      /* #non can be "". */   \
    if(non COND(s)){ /* non is empty */   \
        printf("%c\n", s);    \
     }


int main()
{
    XXX('s', SPACE, !);
    XXX('s', SPACE, );      /* t is right. */
}
