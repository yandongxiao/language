#! /usr/bin/env python
# encoding: utf-8


# 如果要实现DictLike也是需要实现__len__, __getitem__, __delitem__, __setitem__方法
class ListLike:
    def __init__(self):
        self._items = []
    def __getattr__(self, name):
        return getattr(self._items, name)

    # Added special methods to support certain list operations
    # 只有定义了下面的类对象的方法，才能使用对应的函数，如len，下标访问
    def __len__(self):
        return len(self._items)
    def __getitem__(self, index):
        return self._items[index]
    def __setitem__(self, index, value):
        self._items[index] = value
    def __delitem__(self, index):
        del self._items[index]

    def __myself(self):
        print("myself")

# 对于特殊方法(即以双下划线开始并且结尾的变量)的继承原则是全部继承
class subclass(ListLike):
    pass


if __name__ == '__main__':
    a = subclass()
    a.append(2)
    a.insert(0, 1)
    a.sort()
    print(len(a))
    print(a[0])

    a._ListLike__myself()
    a.__myself()
