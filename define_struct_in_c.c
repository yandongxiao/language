#include "struct.h"
#include <stdio.h>

struct ttt_s {
    int a;
};

int main() {
    struct ttt_s t;
    ttt l;
    l.a = 10;
    printf("l.a = %d\n", l.a);
}
