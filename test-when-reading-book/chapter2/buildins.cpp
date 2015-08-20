#include <iostream>
using namespace std;

void value_type ()
{
    int i;

    i = 20;     /* 20 is signed, int<long<long long */
    i = 0x20;
    i = 020;    /* 20 is unsigned or signed. int < unsigned int < long < unsigned long.. */

    /* Note: -20 will be considered as expression. */

    i = 20u;
    i = 20l;
    i = 20ll;

    i = 2.1;    /*double*/
    i = 2.1F;   /*float*/
    i = 2.1L;   /*long double*/
}


/* type cast is every where */
int main ()
{
    /* void */

    /* one byte */
    bool b = true;
    char c = 'c';
    cout << "b:"<<sizeof(b)<<endl;
    cout << "c:"<<sizeof(c)<<endl;

    /* ll > l > i > short >= 16 */
    /* ll >= 64, l >=32, i >= 16 */
    short s = 10;
    int i = 10;
    long l = 10;
    long long ll = 10;
    cout << "s:"<<sizeof(s)<<endl;
    cout << "i:"<<sizeof(i)<<endl;
    cout << "l:"<<sizeof(l)<<endl;
    cout << "ll:"<<sizeof(ll)<<endl;

    /* included in c++ 11 */
    wchar_t wc;
    char16_t c16;
    char32_t c32;

    /* ld=96 or 128, d=64,  f=32 */
    float f;
    double d;
    long double ld;
    cout << "f:"<<sizeof(f)<<endl;
    cout << "d:"<<sizeof(d)<<endl;
    cout << "ld:"<<sizeof(ld)<<endl;

    return 0;
}
