constexpr int test ()
{
    //int a = 0;    /* error */
    return 0;
}


int i;

int main ()
{
    constexpr int val = 100;

    int num = 10;
    //constexpr int val2 = num+100;   /* error : use unconst value. */

    constexpr int cnum = test ();
    constexpr int *pp = &i; /* i must be global val, not local */
}
