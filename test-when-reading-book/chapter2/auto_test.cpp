#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * [auto can be a pointer]
 */
void
auto_be_pointer ()
{
    /* auto can not be array */
    int nums [] = {1, 2, 3, 4}; /* [] must be last. */
    auto a1 = &nums[0];     /* same as auto a1(&nums[0])*/
    auto *a2 = &nums[0];    /* a1 and a2 is same. */
    assert (a1 == a2);

    /**
     * assign by array
     */
    auto va = vals; /* equals to int *va = vals */
    va[0] = 100;
    assert (vals[0] == 100);

    /**
     * keep low pointer
     */
    const char *name = strdup("ubuntu");
    /* the type of a_name is "const char * "*/
    auto a_name = name;
    //a_name[0] = 'U';
    cout << a_name << endl;

    /**
     * discard top pointer
     */
    char * const cname = strdup("ubuntu");
    /* the type of a_cname is "char *" */
    auto a_cname = cname;
    a_cname[0] = 'U';
    a_cname = strdup("another string");
    cout << a_cname << endl;

    /**
     * the type is const int*
     */
    int var = 10;
    auto a_cvar = &var; /* const int* */
    const auto p1 = &var;   /* p2 is int *const */
    auto const p2 = &var;   /* p2 is int *const */
    *p1 = 100;
    *p2 = 100;
    //p1++;
    //p2++; /* so it is error */
}

class People {
public:
    int age;
    string name;
    bool operator== (People &p) {return this->age == p.age && this->name == p.name;}
};

/**
 * auto can be a variable
 */
void
auto_be_variable ()
{
    /* inner type */
    int num = 10;
    auto val1 = num;
    assert (num == val1);

    /* user defined type */
    People p1;
    auto p2 = p1;
    assert (p1 == p2);

    /* rval2 is not a reference, but a variable */
    int &rnum = num;
    auto rval2 = rnum;
    assert (rval2 == rnum);
    assert (&rval2 != &rnum);
}

void auto_with_const ()
{
    int i = 0, &r = i;
    /* both i and ci have memory address. */
    const int ci = i, &cr = ci;

    auto d = &i;    /* int* d = &i */
    auto e = &ci;   /* const int * e=&ci */
    //*e = 10;  /* so it is error */

    const auto f = ci;  /* const int var */
    auto &g = ci;       /* const int & */
    //g = 10;   /* so it is error */
}

void auto_define_two_var ()
{
    /* 10 is int, and a is long */
    long a = 10;
    //auto b = 10, c = a;   /* b and c must have same type */

    auto &c = a;
    c = 20;
    assert (a == 20);
}

int main ()
{
    int num1 = 1000;
    int num2 = 1000;
    auto val = num1 + num2;

    auto_be_pointer ();
    auto_be_variable();
    auto_with_const ();
    auto_define_two_var ();
    return 0;
}
