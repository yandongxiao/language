#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>
#include <sstream>
using namespace std;

void stream_test(istream &is, ostream &os)
{
	string str;
	getline(is, str);
	os << str << endl;
}

int main ()
{
	stream_test(cin, cout);

	ifstream ifs("./stream_test.cc");
	ofstream ofs("./data");
	stream_test(ifs, ofs);

	string str_in("123\n456");
	stringstream iss(str_in);
	stringstream oss;
	stream_test(iss, oss);
	string str_out = oss.str();
	cout << str_out << endl;
	return 0;
}

