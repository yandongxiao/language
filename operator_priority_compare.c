#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *val;
}Test;

int main()
{
    Test *t = NULL;
    
    t = malloc(sizeof(Test));
    t->val  = "nihao";
    printf("%c\n", *t->val);     /* test for priority. -> has high priority. */
}
