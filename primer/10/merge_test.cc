#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>

using namespace std;


int main ()
{
	vector<int> vec1 = {1,3,5,7};
	vector<int> vec2 = {2,4,6,8};
	vector<int> out_vec;
	merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(out_vec));
	for_each(out_vec.begin(), out_vec.end(), [](int v) {cout<< v <<" ";});
	cout << endl;
}

