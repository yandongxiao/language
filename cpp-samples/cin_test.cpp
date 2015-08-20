#include <iostream>
#include <string>

using namespace std;

void test1 ()
{
    string s;
    cin >> s;
    cout << s << endl;
}

void test2()
{
    int a=0;
    int b=0;

    cin >> a >> b;  /* b is zero */

    cout << a <<endl;
    cout << b <<endl;
}

void test3 ()
{
    string s1 = "world";
    string s2 = "hello " + s1;  /* It is OK. */

    cout << s2 << endl;
}

void test4 ()
{
//    string s1('A');   /* It is not legal */
    string s1 = "world";
    string s2 = 'A' + s1;
    cout << s2 << endl;
}

int main ()
{

    //test1 ();
    //test3 ();
    test4 ();
}
