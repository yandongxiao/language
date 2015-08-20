#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main ()
{
	vector<int> vec = {1,2,3,4};

	vec.insert(vec.end(), 5);
	for_each(vec.begin(), vec.end(), [](int v){cout<<v<<endl;});

	auto iter = inserter(vec, vec.begin());
	*iter = 0;
	*iter = 0;
	for_each(vec.begin(), vec.end(), [](int v){cout<<v<<endl;});

	return 0;
}

