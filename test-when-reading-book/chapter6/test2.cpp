#include <vector>
#include <iostream>

using namespace std;

/* redefinition error */
void func (const int){}
//void func (int){}

/* they are same */
void func(const int *);
void func(const int []);
void func(const int [10]);

void func(const char *cp);
void func(const char *begin, const char *end);
void func(const char [], size_t size);

void func (int (*p)[10]){cout<< "int (*p) [10]" <<endl;}
void func (int (&p)[10]){cout<< "int (&p) [10]" <<endl;}

int main ()
{
    int nums[10];
    func(nums);
    func(&nums);


    return 0;
}
