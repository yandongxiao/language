#include <string>
#include <iostream>

using namespace std;

/* you can not change the size of container */

void
string_test ()
{
    string str = "Helloworld";
    /* not foreach, just for */
    for (auto & val : str) {    /* use referentce */
        val = toupper(val); /* how to use toupper */
    }
    cout << str << endl;

    auto len = str.size();
    for (decltype(len) i=0; i!=len; i++ ){
        str[i]=tolower(str[i]);
    }
    cout << str << endl;
}

/* has begin, end member, or array */
void
what_kind_of_object ()
{
    int nums [] = {1,2,3,4,5};
    for (auto val : nums)
        cout << val << endl;
}

int main ()
{
    string_test();
    what_kind_of_object();
    return 0;
}
