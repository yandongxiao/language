#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

void
accumulate_test()
{
	vector<string> strs = { "sa", "sss", "s" };

	string str = accumulate(strs.begin(), strs.end(), string(""),
			[](const string &str1, const string str2){return str1+str2;});
	cout << str << endl;
}

int main() {
	vector<string> strs = { "sa", "sss", "s" };
	sort(strs.begin(), strs.end(),
			[](const string str1, const string &str2) {return str1.size() < str2.size() ? true : false;});
	for_each(strs.begin(), strs.end(),
			[](const string &str) {cout << str << endl;});

	accumulate_test();

	return 0;
}

