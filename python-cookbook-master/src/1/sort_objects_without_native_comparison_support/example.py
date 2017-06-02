#! /usr/bin/python

class attrgetter :
    def __init__(self, attr, *attrs):
        if not attrs:
            if not isinstance(attr, str):
                raise TypeError("attribute name must be a string")
            names = attr.split('.')
            def func(obj):
                for name in names:
                    obj = getattr(obj,name)
                return obj
            self._call = func

    def __call__(self, obj):
        return self._call(obj)


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
