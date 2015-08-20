#include <iostream>
#include <set>
#include <cassert>

using namespace std;

void foreach_set()
{
    const set<int> iset = {1,2,3,4,6,5};

    /* cout 1,2,3,4,5,6*/
    /* if iset is const, iter is set<int>::const_iterator */
    for (auto iter=iset.begin();
        iter != iset.end(); iter++)
    {
        set<int>::const_iterator citer = iter;
        cout << (*iter) << endl;
    }
}

void iter_compare()
{
    string str = "helloworld";

    auto len = str.end() - str.begin();
    assert (len==10);

}

int main ()
{
    foreach_set();
    iter_compare();
    return 0;
}
