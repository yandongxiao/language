class xxx {
public:
    int a;
    int b;
};

int main ()
{
    int a = 10;     /* method 1 */
    xxx b = {10};
    int c{10};
    int d(0);


    short sa{3};
    xxx bb{10};
//    xxx cc(10);   /* error: need constructor */
    d = {20};
    return 0;
}

