#include <iostream>
#include <string>

using namespace std;

class Beverage {
public:
	virtual void display () = 0;
	virtual ~Beverage() = default;
};

class ChinaBeverageWithSalt : public Beverage {
public:
	virtual void display() {cout << "Chinese beverage with salt" << endl;}
	virtual ~ChinaBeverageWithSalt() = default;
};

class ChinaBeverageWithsugar : public Beverage {
public:
	virtual void display() {cout << "Chinese beverage with sugar" << endl;}
	virtual ~ChinaBeverageWithsugar() = default;
};


class BeverageStore {
public:
	void orderBeverage (string type) {
		Beverage *beverage = createBeverage (type);
		beverage->display();
		delete beverage;
	}
	virtual Beverage* createBeverage (string type) = 0;
	virtual ~BeverageStore() = default;
};

class ChinaBeverageStore : public BeverageStore {
public:
	virtual Beverage* createBeverage (string type) {
		if (type=="salt") {
			return new ChinaBeverageWithSalt;
		} else if (type=="sugar"){
			return new ChinaBeverageWithsugar;
		} else {
			return NULL;
		}
	}


};

int
main ()
{
	ChinaBeverageStore beverage_store;
	beverage_store.orderBeverage("sugar");
	beverage_store.orderBeverage("salt");
	return 0;
}
