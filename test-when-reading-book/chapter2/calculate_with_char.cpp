#include <iostream>
#include <climits>

using namespace std;

/* do not use bool char when calculating */
int main ()
{
    /* they are same in memory */
    char c = -1;
    unsigned char uc = -1;
    signed char sc = -1;

    cout << (int)c << endl;
    cout << (int)uc << endl;    /* 255 */
    cout << (int)sc << endl;


    /* the value of c is undefined */
    cout << CHAR_MAX << endl;
    cout << CHAR_MIN << endl;
    c = CHAR_MAX + 1;
    c = CHAR_MIN - 1;

    /* the vlaue of uc is 0 */
    uc = 256;
    cout << (int)uc << endl;
    return 0;
}
