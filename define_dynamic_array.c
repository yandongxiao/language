#include <stdio.h>
#include <string.h>

/*
   This is a feature in C99
   Note: this is not supported on windows.
*/
void func (const int a) {
	char buf[a];
	strcpy(buf, "hellp");
	printf("%s\n", buf);
}

int
main (int argc, char *argv[]) {
	func(argc);     /* you can do like this. */

    const char *a;      /* do not have to initialize */
    a="das";
}
