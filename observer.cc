#include <iostream>
#include <list>
using namespace std;

class Subject;

class Observer {
private:
	Subject *subject;

public:
	Observer (Subject *subject);

	void display (int number) {cout << "get the notify from Subject: " << number << endl;};
	~Observer() {}
};

class Subject {
private:
	list<Observer *> observers;
	int number = 0;

public:
	void registe (Observer *observ) {observers.push_back(observ);}
	void unregiste (Observer *observ) {observers.remove(observ);};
	void notify() {
		for (auto observer : observers) {
			observer->display(number);
		}
	}
	~Subject () {}
};

Observer::Observer(Subject *subject) {
	this->subject = subject;
	subject->registe(this);
}

int main ()
{
	Subject *subject = new Subject;

	Observer obs1(subject);
	Observer obs2(subject);
	subject->notify();

	subject->unregiste(&obs1);
	subject->notify();

	return 0;
}
