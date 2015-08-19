#include <stdio.h>
#include <errno.h>
#include <assert.h>

int main()
{
    int ret = 0;
    char buffer[1024];
    char *line = NULL;
    FILE *file  = NULL;
   
    file = fopen("/tmp/aaa", "w");
    fclose(file);

    file = fopen("/tmp/aaa", "r");  /* different file desctiptor with file1 */
    errno = 0;

    line = fgets(buffer, 1024, file);
    assert(NULL == line);
    line = fgets(buffer, 1024, file);
    assert(NULL == line);
//    assert(buffer[0] == '\0');    /* when return NULL, all contents in @buffer is undefined. */

    assert(0 == errno);
}
