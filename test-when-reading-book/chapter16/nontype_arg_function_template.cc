#include <iostream>

using namespace std;

template <unsigned M>
void length (const char (&buf)[M])
{
    cout << "buffer length is " << M << endl;
}

void test () {cout << "test" << endl; }
typedef void (*NewType)();
template <NewType func>
void call_func()
{
    func();
}

int a = 20;

template <int *p>
void print_p()
{
    cout << *p << endl;
}

const int b = 30;
template <int p>
void print_val()
{
    cout << p << endl;
}

int main ()
{
    length("dsadsa");
    length("");

    call_func<test>();
    print_p<&a>();

    print_val<b>();

    return 0;
}
