void
test1 (int a [10]) { }

void
test2 (int (*p)[10]) {}

int main ()
{
    int a [10];
    int b [20];

    test1 (a);
    test2 (&a); /* note the & */

    /*error*/
    test1 (b);
//    test2 (&b);   /* error. */
}
