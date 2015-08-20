#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto iter = vec.begin();

	while (iter != vec.end()) {
		if (*iter % 2) {
			iter = vec.insert(iter, *iter);
			iter+=2;
		} else {
			iter = vec.erase(iter);
		}
	}

	for (auto val : vec) {
		cout << val << " ";

	}
	cout<<endl;
	return 0;
}


