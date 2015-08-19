#include <stdio.h>

void test2 ();


int main(void)
{
    struct AAA {
        int aaa;
    };
    typedef void func (void);

    struct AAA aaa;
    func *f;
    aaa.aaa = 10;
    printf ("%d\n", aaa.aaa);

    test2();
}


void test()
{

//    struct AAA aaa;
//    func *f;
}

    typedef void func (void);   /* can not be in struct block. */
struct mm {
    func *f;
};

void test2 ()
{
    int a = 0;

    printf ("%d\n", sizeof(struct mm));
}

