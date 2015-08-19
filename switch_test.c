#include <stdio.h>

int main (void)
{
    int i = 0;
    for (i=0; i<10; i++) {
        printf ("for begin\n");
        switch (i) {
            case 0:
                printf ("break\n");
                break;

            case 1:
                printf ("continue\n");
                continue;

        }

        printf ("for end\n");
    }

    return 0;
}
