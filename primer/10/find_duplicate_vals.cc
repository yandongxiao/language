#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>

using namespace std;

void adjacent_find_test() {
	vector<int> vec = { 1, 2, 3, 4, 5, 5, 6 };
	auto iter = adjacent_find(vec.begin(), vec.end());
	for_each(iter, vec.end(), [](int val) {cout << val << endl;});

	iter = adjacent_find(vec.begin(), vec.end(),
			[](int v1, int v2) {return v1==v2;});
	for_each(iter, vec.end(), [](int val) {cout << val << endl;});
}

void search_n_test() {
	vector<int> vec = { 1, 2, 3, 4, 5, 5, 6 };
	auto iter = search_n(vec.begin(), vec.end(), 2, 5);
	for_each(iter, vec.end(), [](int val) {cout << val << endl;});

	iter = search_n(vec.begin(), vec.end(), 2, 5, [](int v1, int v2) {return v1==v2;});
	for_each(iter, vec.end(), [](int val) {cout << val << endl;});
}

int main() {
	search_n_test();
	return 0;
}

