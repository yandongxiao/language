#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

int i1 = 1;
int i2 = 2;
int i3 = 3;
int i4 = 4;
int i5 = 5;
int i6 = 6;
int i7 = 7;
int i8 = 8;
int i9 = 9;

void
nine_arguments(int i1,int i2,int i3,int i4,int i5,int i6,int i7,int i8,int & i9)
{
	cout << i1++ << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9++ << endl;
}

int main() {
	nine_arguments(i1, i2, i3, i4, i5, i6, i7, i8, i9);

	bind(nine_arguments, i9, i8, i7, i6, i5, i4,
			_1,
			_2,
			i1)(1,2);

	auto func = bind(nine_arguments, i9, i8, i7, i6, i5, i4,
			_1,
			i2,
			ref(i1));
	func (3);
	func (3);

}

