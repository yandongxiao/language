#include <stdio.h>

typedef enum _score {
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6
} score_t;

int
main (void) 
{
    printf ("sizeof (score_t) == %d\n", sizeof (score_t));
    return 0;
}
