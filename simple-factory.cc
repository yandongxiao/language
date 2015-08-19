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

class BeverageFactory {
public:
	Beverage* createBeverage (string type) {
		if (type=="salt") {
			return new ChinaBeverageWithSalt;
		} else if (type=="sugar"){
			return new ChinaBeverageWithsugar;
		} else {
			return NULL;
		}
	}
};

class BeverageStore {
private:
	BeverageFactory *factory;
public:
	BeverageStore(BeverageFactory *factory) {this->factory=factory;}
	void orderBeverage (string type) {
		Beverage *beverage = factory->createBeverage(type);
		beverage->display();
		delete beverage;
	}
	~BeverageStore() {delete factory;};
};

int
main ()
{
	BeverageStore beverage_store(new BeverageFactory);
	beverage_store.orderBeverage("sugar");
	beverage_store.orderBeverage("salt");
	return 0;
}
