#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* test if setenv */
int main ()
{
    char *str1 = strdup("aaa");
    char *str2 = strdup("bbb");
    char *str3 = strdup("ccc");

    setenv ("str1", NULL, 1);
    setenv ("str2", str2, 1);
    setenv ("str3", str3, 1);

    if (fork()==0) {
        printf ("%s==%s\n", "str1", getenv ("str1"));
        printf ("%s==%s\n", "str2", getenv ("str2"));
        printf ("%s==%s\n", "str3", getenv ("str3"));
        return 0;
    }

    printf ("%s==%s\n", "str1", getenv ("str1"));
    printf ("%s==%s\n", "str2", getenv ("str2"));
    printf ("%s==%s\n", "str3", getenv ("str3"));

    return 0;
}
