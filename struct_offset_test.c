#include <event.h>
#include <assert.h>

typedef struct abc {
	int a;
	int b;
}abc_t;

int
main(void) {
	long int off = (int)&(((abc_t*)0)->a);   /* will have a warnning */
	printf("a off is :%lu\n", off);

	off = (int)&(((abc_t*)0)->b);    
	printf("a off is :%lu\n", off);
}

