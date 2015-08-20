#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

void
partition_test()
{
	cout << __func__ << endl;

	vector<string> strs = { "sa", "sss", "s" };
	auto iter = partition(strs.begin(), strs.end(), [](const string &str){return str.size()>2 ? true : false;});
	for_each(strs.begin(), strs.end(),
			[](const string &str) {cout << str << endl;});

	for_each(strs.begin(), iter,
			[](const string &str) {cout << str << endl;});

}

int main() {
	partition_test();
	return 0;
}

