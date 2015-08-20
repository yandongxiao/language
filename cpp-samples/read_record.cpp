#include <iostream>

using namespace std;

#define enter() cout << __func__ << endl

class record {

public:
    double price;
    unsigned number;
    
    record (record &);
    record ();
    record (double price, int number);
    record (double price) {}

    void method (record rd) {}
    record& operator = (record &rd);
    record  operator + (record &r2);
    /* because this can not be the first parameter */
    friend istream& operator >> (istream &in, record &r);
    friend ostream& operator << (ostream &out, record &r);
};

record::record ()
{
    enter ();
    this->price = 0;
    this->number = 0;
}

record::record (record &rd)
{
    cout << "record (record &rd)" <<endl;
    this->price = rd.price;
    this->number = rd.number;
}

record::record (double price, int number)
{
    enter ();
    this->price = price;
    this->number = number;
}

record& record::operator = (record &rd)
{
    enter ();

    this->price = rd.price;
    this->number = rd.number;

    return *this;
}

record record::operator + (record &r2)
{
    enter ();
    record result;
    result.price = this->price;
    result.number = this->number + r2.number;

    return result;
}

istream& operator >> (istream &in, record &r)
{
    enter ();
    if (in >> r.price)
        in >> r.number;

    return in;
}

ostream& operator << (ostream &out, record &r)
{
    enter ();
    out << r.price << " * " 
        << r.number << " = " 
        << r.price * r.number 
        << endl;

    return out;
}

int main ()
{
    record rd;

    cout << "input you record" << endl;
    cin >> rd;
    cout << rd;

    record newrd = rd;
    newrd = rd;

//    rd.method(3.0);   /* there is no type cast */
    rd = 3.0;
    return 0;
}
