#include <iostream>

using namespace std;

class Head {
public:
	virtual void showHead() = 0;
	virtual ~Head(){}
};

class ChinaHead : public Head {
public:
	void showHead () {cout << "china heade" << endl;}
	virtual ~ChinaHead(){}
};

class Eye {
public:
	virtual void showEye() = 0;
	virtual ~Eye(){}
};

class ChinaEye : public Eye {
public:
	virtual void showEye() {cout << "china eye" << endl; }
	virtual ~ChinaEye(){}
};

class Leg {
public:
	virtual void showLeg() = 0;
	virtual ~Leg(){}
};

class ChinaLeg : public Leg {
public:
	virtual void showLeg() {cout << "china leg" <<endl; }
	virtual ~ChinaLeg(){}
};

class AbstractFactory {
public:
	virtual Head* createHead () = 0;
	virtual Eye*  createEye() = 0;
	virtual Leg*  createLeg() = 0;
	virtual ~AbstractFactory() {}
};

class ChinaFactory : public AbstractFactory {
public:
	virtual Head* createHead () { return new ChinaHead;};
	virtual Eye*  createEye() {return new ChinaEye;};
	virtual Leg*  createLeg() {return new ChinaLeg;};
	virtual ~ChinaFactory() {}
};

class Toys {
	Head *head;
	Eye *eye;
	Leg *leg;

public:
	Toys (AbstractFactory *factory) {
		head = factory->createHead();
		eye = factory->createEye();
		leg = factory->createLeg();

		delete factory;
	}

	void display () {
		head->showHead();
		eye->showEye();
		leg->showLeg();
	}
};

int main ()
{
	Toys *t = new Toys(new ChinaFactory);
	t->display();

	return 0;
}