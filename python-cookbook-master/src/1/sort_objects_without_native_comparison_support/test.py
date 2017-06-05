#!/usr/bin/env python
# encoding: utf-8

class attrgetter(object):
    def __init__(self, attr, *attrs):
        if attrs:
            attrs = (attr, ) + attrs
            def func(obj):
                return tuple(getattr(obj, i) for i in attrs)
        else:
            def func(obj):
                return getattr(obj, attr)
        self._func = func

    def __call__(self, obj):
        return self._func(obj)


class User:
    def __init__(self, user_id):
        self.user_id = user_id
    def __repr__(self):
        return 'User({})'.format(self.user_id)

# Example
users = [User(23), User(3), User(99)]
print(users)

# Sort it by user-id
print(sorted(users, key=attrgetter('user_id')))
