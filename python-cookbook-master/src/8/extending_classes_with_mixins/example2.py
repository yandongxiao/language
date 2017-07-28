#! /usr/bin/env python3
# encoding: utf-8


class RestrictKeysMixin(object):
    # 这个混入类是有状态的
    # 虽然RDict没有__init__方法，但是默认实现的方式会去调用基类的方法
    def __init__(self, *args, _restrict_key_type, **kwargs):
        self.__restrict_key_type = _restrict_key_type
        # 这一句是必须的哟
        super().__init__(*args, **kwargs)

    def __setitem__(self, key, value):
        if not isinstance(key, self.__restrict_key_type):
            raise TypeError('Keys must be ' + str(self.__restrict_key_type))
        super().__setitem__(key, value)


class RDict(RestrictKeysMixin, dict):
    pass


d = RDict(_restrict_key_type=str)
e = RDict([('name','Dave'), ('n',37)], _restrict_key_type=str)
f = RDict(name='Dave', n=37, _restrict_key_type=str)
print(e)
print(f)
try:
    f[42] = 10
except TypeError as e:
    print(e)
