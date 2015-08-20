#include <iostream>
#include <vector>
#include <string>

using namespace std;

class example {
public:
    int a;
    example () = default;
    example (example &e) {this->a = 10;}
    example (int a) {this->a = a;}
};

void test (vector<string> vec)
{
    cout << "test" << endl;
}

int main ()
{
    example e;
    example ev = e;
//    example evv = 10;
    
    vector<string> vec(110);

    /* see page 266 */
    test (static_cast<vector<string>>(10));

    cout << ev.a << endl;
    return 0;
}
