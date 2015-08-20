#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>

using namespace std;

class TTT {
public:
	TTT() = default;
	TTT(const TTT &t) {cout << "TTT(const TTT &t)" <<endl;}
//	TTT(TTT &&t) noexcept {cout << "TTT(TTT &&t)" <<endl;}
};

void
move_test()
{
	vector<TTT> vec(2);

	vector<TTT> dest;

	move(vec.begin(), vec.end(), back_inserter(dest));
	cout << dest.size() << endl;
}


int main ()
{
	move_test();

	return 0;
}

