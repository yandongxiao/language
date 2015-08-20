#include <vector>
#include <iostream>

using namespace std;

#define enter() cout << __FUNCTION__ << endl

class record {

public:
	double price;
	unsigned number;

	record(record &);
	record();
	record(double price, int number);

	record& operator = (record &rd);
	record  operator + (record &r2);
	/* because this can not be the first parameter */
	friend istream& operator >> (istream &in, record &r);
	friend ostream& operator << (ostream &out, record &r);
};

record::record()
{
	enter();
	this->price = 0;
	this->number = 0;
}

record::record(record &rd)
{
	cout << "record (record &rd)" << endl;
	this->price = rd.price;
	this->number = rd.number;
}

record::record(double price, int number)
{
	enter();
	this->price = price;
	this->number = number;
}

record& record::operator = (record &rd)
{
	enter();

	this->price = rd.price;
	this->number = rd.number;

	return *this;
}

record record::operator + (record &r2)
{
	enter();
	record result;
	result.price = this->price;
	result.number = this->number + r2.number;

	return result;
}

istream& operator >> (istream &in, record &r)
{
	enter();
	if (in >> r.price)
		in >> r.number;

	return in;
}

ostream& operator << (ostream &out, record &r)
{
	enter();
	out << r.price << " * "
		<< r.number << " = "
		<< r.price * r.number
		<< endl;

	return out;
}

template <class T>
class MyArray {
	T elmts[12];
};

int main()
{
	MyArray<record> array;
}
