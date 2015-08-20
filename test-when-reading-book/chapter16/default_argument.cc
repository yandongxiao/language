#include <algorithm>

bool compare (int a, int b)
{
	return false;
}

using MyType = decltype(compare);

int main ()
{
	MyType *type = MyType();
	return 0;
}
