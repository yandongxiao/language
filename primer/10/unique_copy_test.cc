#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

void
unique_copy_test()
{
	vector<int> vec = {1,2,2,3,3,4,4,4};

	list<int> lt;

	unique_copy(vec.cbegin(), vec.cend(), inserter(lt, lt.begin()));
	for_each(lt.cbegin(), lt.cend(), [](int val){cout<<val<<" ";});
	cout << endl;
}

int main ()
{
	unique_copy_test();

	return 0;
}

