#include <iostream>

using namespace std;

class TTT {
    int a;
    int b;

public:
    /**
     * declared as friend
     * return the reference of cin and cout
     */
    friend istream& operator >> (istream &in, TTT &t);
    friend ostream& operator << (ostream &out, const TTT &t);

};

istream&
operator >> (istream &in, TTT &t)
{
    if (in)
        in >> t.a;

    if (in)
        in >> t.b;

    return in;
}

ostream&
operator<< (ostream &out, const TTT &t)
{
    out << t.a << " , " << t.b << endl;
    return out;
}

int main ()
{
    TTT t1, t2;
    cin >> t1 >> t2;

    cout << t1 << t2;
    return 0;
}
