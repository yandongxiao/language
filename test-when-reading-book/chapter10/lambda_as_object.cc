#include <iostream>
using namespace std;

int main ()
{
	int num = 10;
	/* the type of num is: const int num */
//	auto func = [num](){cout << num-- << endl;};

	/* mutable lambda */
	auto func = [num] () mutable {cout << num-- << endl;};

	func();
	func();
	cout << num << endl;
}

