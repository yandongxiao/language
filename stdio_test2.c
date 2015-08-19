#include <stdio.h>
#include <limits.h>
#include <assert.h>
int
main (void)
{
    char buff[BUFSIZ];
    FILE *stream = fopen ("/tmp/aaa", "w+");
    setbuf (stream, buff);

    /* use gdb to check */    
    fputs ("hello", stream);
    fputs ("world", stream);
    
    fseek (stream, 0, SEEK_SET);
    int c = getc (stream);
    printf ("getc == %c\n", (char)c);
    ungetc (c, stream); /* set it to -1. */
    printf ("ungetc == %c\n", (char)c);
    c = getc (stream);
    assert ('h' == c);

    fseek (stream, 0, SEEK_END);
    fputs ("done\n", stream);

    return 0;
}
