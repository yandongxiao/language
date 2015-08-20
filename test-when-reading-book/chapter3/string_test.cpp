#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

/* use string instead of c_style string */
#include <cctype>   /* handlesingle character, e.g. toupper */
using namespace std;

class TTT {
public:
    int a;
    TTT (const TTT &t);
    TTT();
};

TTT::TTT () = default;

TTT::TTT (const TTT &t)
{
    cout << "TTT(TTT &) called" << endl;
    this->a = t.a;
}

void init2()
{
    TTT t;
    t.a = 10;
    
    /* TTT(const TTT &t) will be called */
    TTT t2 = t;
    TTT t3(t);
    TTT t4{t};
    TTT t5 = {t};
}

void init()
{
    /* 1 */
    string str1;
    
    /* 2 */
    string str2 = str1;
    string str3(str1);
    string str4 = {str1};
    string str5{str1};

    /*same with up, have other kinds */
    string str6 = "hello";

    // string str7(10); /* not include */
    string str8(10, 'd');
}

void lookup()
{
    /* all containers in STL have these methods */
    string str = "helloworld";
    cout << str.size() << endl;
    cout<<str.capacity()<<endl;
    str.empty();

    /* the return type is size_t !! */
    auto p = str.find("world");
    if (p != string::npos)
        cout << "FOUND " << str.substr (p) << endl;

    auto r = find (str.cbegin(), str.cend(), 'c');
    assert (r == str.cend());
}

void
getline_test()
{
    string str;
    while(getline(cin, str)) {
        cout << "line:" << str <<endl;
    }

}

void
operator_test ()
{
    string str = "hello";
    string str2;

    str2 = str;
    str2 += str;
//    str2 = str2 * 3;  /* no included */
    str2 == str;
    str2 >= str;

    str += "dsa";
    str  = "ddd" + str; /* as the first param */
    str += 'a';
    const char *p = str.c_str();
}

int main ()
{
    init ();
    init2();
    lookup();
    getline_test();
    operator_test();
}
