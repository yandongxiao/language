#include <iostream>
#include <vector>

using namespace std;

/* In std namespace, there are also a function named max. */
/* I want handle the next two case : max (a, b) and max (1,2). 
  *
  * look up the vector->begin function, we know that:
  *      the reason why begin can return iterator and const_iterator both is that begin method is
  *      overloaded. by const. iterator begin() and const_iterator begin().
  * But function max can not do like this.
  */
template <typename T>
T & max(T &a, T &b)
{
	return a >= b ? a : b;
}

/*
  * this is from the global function begin.
  * we know that : If you pass the array to a function template, then you can get the size too.
  */
template<class _Ty, size_t _Size>
size_t array_size(_Ty(&_Array)[_Size])
{
	return _Size;
}

int main()
{
	int a = 3;
	int b = 4;

	const int &val = ::max(a, b);
	cout << ::max(a, b) << endl;
	int sa[10];
	cout << ::array_size(sa) << endl;
}
