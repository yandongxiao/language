#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>

using namespace std;

int main ()
{
	ifstream stream("data/readme");
	istream_iterator<string> iter = stream;
	istream_iterator<string> iter_eof;

	vector<string> vec(iter, iter_eof);

	ostream_iterator<string> out_iter(cout, " ");
	copy(vec.begin(), vec.end(), out_iter);

	return 0;
}

