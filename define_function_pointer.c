/*
 * 1. hello is a function pointer actually.
 * 2. cb is a variable that points to function.
 * 3. the cb=hello will produce warnning if the type of arguments have difference.
 * 4. int main() is different main(void)
 */
#include <stdio.h>

static void
hello(int a, void*b)
{

}

/* the second format is the normally used case. */
//typedef void (hcb)(int a, void *b);
typedef void (*hcb)(int a, void *b);

int
main(void)
{
    hcb cb = hello;
    cb(10, "abc");
}
