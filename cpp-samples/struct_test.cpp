#include <cassert>

struct Sale_item {
    int price1 = 10;
    int price2 = {20};
    int price3;
    Sale_item(){}
};

int main ()
{
    Sale_item item;
    assert (item.price1 == 10);
    assert (item.price2 == 20);
    assert (item.price3 == 0);

}
