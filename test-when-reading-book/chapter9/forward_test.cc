#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
using namespace std;

int main() {
	forward_list<int> vec = { 0, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto iter = vec.begin();
	auto pre_iter = vec.before_begin();
	while (iter != vec.end()) {
		if (*iter % 2) {
			vec.insert_after(pre_iter, *iter);
			pre_iter = iter;
			iter++;
		} else {
			iter = vec.erase_after(pre_iter);
		}
	}

	for (auto val : vec) {
		cout << val << " ";

	}
	cout<<endl;
	return 0;
}


