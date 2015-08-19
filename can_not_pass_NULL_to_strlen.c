#include <stdio.h>
#include <string.h>

int main()
{
    strlen(NULL);		/* ok */
    int a = strlen(NULL);	/* no */
    return 0;
}
