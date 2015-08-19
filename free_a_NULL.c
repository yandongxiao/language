#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(10);
    free(buf);
    buf=NULL;
    free(buf);
}
