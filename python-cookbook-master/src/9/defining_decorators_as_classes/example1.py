# Example of defining a decorator as a class
import types
from functools import wraps

class Profiled:
    def __init__(self, func):
        # 使用到了wraps的本质
        wraps(func)(self)
        self.ncalls = 0

    def __call__(self, *args, **kwargs):
        self.ncalls += 1
        return self.__wrapped__(*args, **kwargs)

    # 由于装饰器应用在了方法上，所以需要实现__get__方法
    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            return types.MethodType(self, instance)


# add = Profiled(add)
@Profiled
def add(x, y):
    return x + y

class Spam:
    # bar = Profiled(bar)
    @Profiled
    def bar(self, x):
        print(self, x)

if __name__ == '__main__':
    print(add(2,3))
    print(add(4,5))
    print('ncalls:', add.ncalls)

    s = Spam()
    s.bar(1)
    s.bar(2)
    s.bar(3)
    print('ncalls:', Spam.bar.ncalls)
