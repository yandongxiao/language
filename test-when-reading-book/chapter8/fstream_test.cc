#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>
#include <sstream>
using namespace std;

void fstream_test()
{
	ifstream ifs("./abc");
	if (! ifs) {
		cout << "can not use" <<endl;
	}

	ifs.open("./src/helloworld.cpp");
	if (ifs) {
		cout << "ok to use" << endl;
	}
}

int main ()
{
	fstream_test();
	return 0;
}

