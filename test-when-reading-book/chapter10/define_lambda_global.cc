#include <iostream>
#include <string>

using namespace std;

auto isShorter = [] (const string str1, const string str2) {return str1<str2;};

int main ()
{
	cout << isShorter("nihao", "nihay") << endl;
}

