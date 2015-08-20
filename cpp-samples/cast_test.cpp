int main ()
{
    double d = 3.14;
    int a = d + 1;

    void *pv = &a;
    char *pc = static_cast<char*>(pv);
//    long *pl = static_cast<long*>(pc);    /* cast error*/
    long *pl = reinterpret_cast<long*>(pc);
    *pl = 10;
    
    return a;
}
