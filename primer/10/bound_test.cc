#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>

using namespace std;

void
lower_bound_test()
{
	int nums[] = {1,2,3,4,5,5,6,6,7};
	auto iter = lower_bound(begin(nums), end(nums), 5);
	cout << iter-begin(nums) << endl;

	 iter = upper_bound(begin(nums), end(nums), 5);
	 cout << iter-begin(nums) << endl;

	 auto pair = equal_range(begin(nums), end(nums), 5);
	 cout << pair.first-begin(nums) << "--" << pair.second-begin(nums) << endl;

}

int main ()
{
	lower_bound_test();

	return 0;
}

