#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

void
stream_iterator_test1()
{
	istream_iterator<int> iter = cin;
	istream_iterator<int> iter_eof;

	*iter;
	*iter;
	iter++;
	int val = *iter;
	cout << val << endl;
}

void
stream_iterator_test2()
{
	istream_iterator<int> iter = cin;
	istream_iterator<int> iter_eof;

	iter++;
	iter++;
	cout << *iter << endl;
}

void
stream_iterator_test3()
{
	istream_iterator<int> iter = cin;
	istream_iterator<int> iter_eof;

	auto begin = iter;
	auto pos = find(iter, iter_eof, 4);
	/* no thing */
	for_each(begin, pos, [](int val){cout << val <<endl;});
}

int main ()
{
	stream_iterator_test3();
	return 0;
}

