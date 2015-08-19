#include <iostream>

using namespace std;

class Beverage {
public:
	virtual double price() { return 10.0;}
	virtual ~Beverage () {}
};

class BeverageWithSugar : public Beverage {
private:
	Beverage *beverage;

public:
	BeverageWithSugar(Beverage *bevarage) {this->beverage = bevarage;}
	double price() {return 1 + beverage->price();}

	virtual ~BeverageWithSugar() {}
};

class BeverageWithSalt : public Beverage {
private:
	Beverage *beverage;
public:
	BeverageWithSalt(Beverage *beverage) {this->beverage = beverage;}
	double price() {return 1 + beverage->price();}
	virtual ~BeverageWithSalt() {}
};

int main ()
{
	Beverage *beverage = new Beverage();
	beverage = new BeverageWithSugar(beverage);
	beverage = new BeverageWithSalt(beverage);

	cout << beverage->price() <<endl;

	delete beverage;
	return 0;
}
