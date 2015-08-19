#include <stdio.h>

struct XXX {

    void *** a;
};

int main(void)
{
    printf("%d\n", sizeof(struct XXX));

    return 0;
}
