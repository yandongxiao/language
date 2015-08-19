#include <stdio.h>

#define _int int

#define HOST(name, type)  \
    struct name {   \
        _##type host; \     /* the @type must be the arguments of HOST. */
    }

#define ASD val
#define STRING 

#define HOST_2(name, val)  \
    struct mm {   \
        char *name; \
        int val;   \
    }

int main ()
{
     HOST (h1, int);
    HOST_2(h2, dsa);
//    HOST_2(h3, val);

    printf ("%d\n", sizeof (struct host));
    printf ("%s\n", STRING);
}
