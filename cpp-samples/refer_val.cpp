#include <assert.h>

int test1 ()
{
    int ival = 1.01;
//    int &rval1 = 1.01;    /* error */
    int &rval2 = ival;
//    int &rval3;   /* error */

}


void test2 ()
{
    int i=0, &r1 = i;
    r1 = 10;
    assert (i == 10);

    int *p1 = &r1;   /* sucess */
    int *p2 = &i;
    assert (p1 == p2);
    

    double d=0, &r2 = d;

    r2 = 3.13159;
    r2 = r1;
    i = r2;
    r1 = d;
}

void test3 ()
{
    double d;
//    int *p = (double*)&d;   /* error */
    int *rp = nullptr;
}

int main ()
{
    test2 ();
}
