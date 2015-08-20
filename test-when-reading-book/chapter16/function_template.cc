#include <iostream>
using namespace std;

template<typename T>
const T& lager (const T &t1, const T &t2)
{
    return t2>t1 ? t2 : t1;
}

int main ()
{
    cout << lager(5, 3) << endl;

    string str1 = "nidsao";
    string str2 = "nidsap";

    cout << lager(str1, str2) << endl;

    return 0;
}
