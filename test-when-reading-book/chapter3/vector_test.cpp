#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

/* use vector instead of array */

void init()
{
    vector<int> ivec1;
    vector<int> ivec2 = ivec1;
    vector<int> ivec3 = {1, 2, 3};  /* can not set 3.3 */
    vector<int> ivec4(10);
    vector<int> ivec5(10, 1);
    vector<int> ivec6{10};

    assert (ivec4[0]==0);   /* int will be initialized 0 */

    /* not the same type */
//    vector<double> dvec = ivec1;
    vector<double> dvec(ivec4.begin(), ivec4.end());

    /* because 10 can not converted to string object.
     * equal to vector<string> vstr1(10)
     */
    vector<string> vstr1{10};


//    vector<const int> ttt(10);    /* compire error */
}

void
operate()
{
    vector<int> ivec;

    /* same as string */
    ivec.size();
    ivec.capacity();
    ivec.empty();


    vector<int> ivec2(10);
//    ivec = ivec + ivec2;    /* not supported */
    ivec >= ivec2;
    ivec == ivec2;

    ivec.push_back(10);
    ivec.pop_back();
    ivec.front();
    ivec.back();

    ivec.insert(ivec.end(), ivec2.begin(), ivec2.end());
    assert (ivec.size()==10);
}

int main ()
{
    init();
    return 0;
}
