#include <iostream>

using namespace std;

class Single {
private:
	static Single *single;
	Single() { single=this; number=10; }

public:
	int number = 0;

	static Single * create () {
		if (single) {
			return single;
		}

		return new Single;
	}

	void display () {
		cout << "number == " << number << endl;
	}
};

Single* Single::single = NULL;

int main ()
{
	Single *single = Single::create();
	single->display();

	Single *single2 = Single::create();
	single->display();
	single2->number = 100;

	single->display();

	return 0;
}
