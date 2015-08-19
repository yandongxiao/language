#include <stdio.h>
#include <errno.h>
#include <assert.h>
int main() {
    FILE *f = fopen("/tmp/conf", "r");

    char buf[1024];
    errno = 0;
    fgets(buf, 1024, f);
    printf("errno = %d\n", errno);
    printf("%s\n", buf);

    assert(NULL == fgets(buf, 1024, f));    /* errno has not been set.*/
    printf("errno = %d\n", errno);
    printf("%s\n", buf);
}
