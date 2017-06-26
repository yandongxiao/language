#! /usr/bin/env python3
# encoding: utf-8

# 在子类中扩展一个property可能会引起很多不易察觉的问题，因为一个property其实是 getter、setter 和 deleter 方法的集合
# 只修改其中一个方法，装饰符变成了Person.name.setter.
# 我们知道property的魔法是基于描述符的，get,set,del方法都是在描述符的实例对象当中. 描述符的实例对象也是类对象的一个属性
# 如果只修改一个方法，需要确保直接修改的是描述符的实例对象

class Person:
    def __init__(self, name):
        self.name = name

    # Getter function
    @property
    def name(self):
        return self._name

    # Setter function
    @name.setter
    def name(self, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        self._name = value

    @name.deleter
    def name(self):
        raise AttributeError("Can't delete attribute")

# 修改name的所有方法时
# 装饰符不用改变
class SubPerson(Person):
    @property
    def name(self):
        print('Getting name')
        return super().name

    @name.setter
    def name(self, value):
        print('Setting name to', value)
        # 在Person类当中name是类Person的一个属性，也是property类的一个实例
        # name对象拥有__get__,  __set__, __delete__方法（其实就是Person中的三个方法）
        # super(SubPerson, SubPerson) 代表父类本身
        # NOTE: 还是不是太懂super的工作原理
        super(SubPerson, SubPerson).name.__set__(self, value)

    @name.deleter
    def name(self):
        print('Deleting name')
        super(SubPerson, SubPerson).name.__delete__(self)

# 只修改其中一个方法
# 注意装饰符变成了Person.name.setter
class SubPerson2(Person):
    # 多了一个父类的类名称
    @Person.name.setter
    def name(self, value):
        print('Setting name to', value)
        super(SubPerson2, SubPerson2).name.__set__(self, value)

# 只修改其中一个方法
# 注意装饰符变成了Person.name.getattr
class SubPerson3(Person):
    # 上面的可是@property
    @Person.name.getter
    def name(self):
        print('Getting name')
        return super().name     # 为什么这里又是这种方法

if __name__ == '__main__':
   a = SubPerson('Guido')
   print(a.name)
   a.name = 'Dave'
   print(a.name)
   try:
       a.name = 42
   except TypeError as e:
       print(e)
