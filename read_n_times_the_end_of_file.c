#include <stdio.h>
#include <assert.h>

int main()
{
    int ret = 0;
    char buffer[1024];
    FILE *f = fopen("/tmp/aaa", "r");

    char *line;

    line= fgets(buffer, 1024, f);
    assert(NULL == line);

    line= fgets(buffer, 1024, f);
    assert(NULL == line);
    
    line= fgets(buffer, 1024, f);
    assert(NULL == line);
}
