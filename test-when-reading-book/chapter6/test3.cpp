#include <vector>
#include <iostream>
#include <initializer_list>

using namespace std;

/* compatible with C, ',' option */
void
test1 (int val, ...){}

/* initializer_list */
void
test2 (int val, initializer_list<int> strs){}

void
initializer_test()
{
    initializer_list<int> val1;
    initializer_list<int> val2 = val1;
    initializer_list<int> val3 = {1,2,3,4};

    val3.size();
    for (auto &val : val3) {
        cout << val << endl;
        /* the type of val is const int & */
//        val = 100;
    }
    
    /* so we do not have method to add/remove elements in initializer_test */
}

int main ()
{
    initializer_test();

    test1(1, 2, 3);
    test2(1, {2,3});
    return 0;
}
