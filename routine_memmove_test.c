/*
 * you can set the third arguments zero, but you'd better check it to avoid invoking it.
 */
#include <string.h>

int main() {
	char buf[10];
	void *d = memmove(buf, NULL, 0);	/* OK */
}
