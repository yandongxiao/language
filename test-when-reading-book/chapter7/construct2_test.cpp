#include <vector>
#include <iostream>

using namespace std;

class TTT {
    /* define a const value
     * 1. init way one
     */
    const int val  = 10;
    const int val2; /* must init, or compile error */
public:
    /* init way two */
    TTT() : val2(1) {cout <<"TTT()"<<endl;}
    TTT(TTT &t) : TTT() {cout <<"TTT(TTT &)"<<endl;}
};

class QQQ {
    int val;
public:
    QQQ(int val){cout << "QQQ(int val)" << endl;}
    QQQ(const QQQ &q) {cout <<"QQQ(QQQ &q)" << endl;}
    ~QQQ() {cout <<"~QQQ()" << endl;}
    void combine(QQQ &q) {cout << "combine(QQQ &q)" <<endl;}
    void combine(QQQ q) {cout << "combine(QQQ q)" <<endl;}
};

int main ()
{
    /* no such initi, it define a function, named t */
//    TTT t();

    TTT t;       /* you have no chance to chage @val2 */
    TTT t2 = t;

    int a = int();  /* value init, 0*/

    
    /* just like QQQ q = QQQ(a) */
    QQQ q = a;
    q.combine(QQQ(10));

    /* you confused c++ compiler */
//    q.combine(q);
    return 0;
}
