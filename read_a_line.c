#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

static int default_line_len = 1024;

char *
read_line (FILE *stream)
{
    char cin;
    int maxsize;
    int len;
    char * line = NULL;

    maxsize = default_line_len;
    line = (char*)malloc(maxsize);
    assert(NULL != line);

    len = errno = 0;
    /* fgets read at most one less than size characters, appends '\0' */
    while (fgets(line+len, maxsize-len, stream) != NULL) {
        len = strlen(line);
        if (len==maxsize-1 && line[len-1] != '\n') { /* and line[len]='\0', So there are more data in the line.*/
            maxsize += default_line_len - 1;
            line = realloc(line, maxsize);
            assert(NULL != line);
            continue;
        }
        break;
    }
    
    if (0 != errno) {
        error("fgets read error");
        free(line);
        return NULL;
    }

    if (len == 0) { /* read to the end of file.*/
        free(line);
        return NULL;
    }

    return line;
}

int
main(void)
{
    FILE *fp;
    fp = fopen("/tmp/profile", "r");
    char *line;
    int i = 0;
    while((line = read_line(fp)) != NULL) {
        printf("%s", line);
        free(line);
        i++;
 }
}

