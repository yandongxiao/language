#include <stdio.h>
#include <stdlib.h>

struct str {
    int len;
    char s[0];      /* lea instruction */
};

struct foo {
    struct str *a;
};

int 
test1 (void)
{
    struct foo f = {0};
    if (f.a->s){    /* this is a address : 4 */
        printf("%d\n", f.a->s);     /* s is a pointer */
//      printf("%d\n", f.a->len);   /* its type is int, here try to get the content. */
    }
    return 0;
}

int
test2 (void)
{
    struct foo f;
    f.a = malloc (sizeof (struct str));
    f.a->len = 10;
    if (f.a->s) {    /* both f.a and f.a-s jie referrence */
        printf("%p\n", f.a);
        printf("%p\n", &f.a->len);  /* the same reason */
        printf("%p\n", f.a->s);
        printf("%d\n", f.a->len);
    }
    return 0;
}

int
main (void)
{
    test1 ();
    test2 ();
    return 0;
}
