#! /usr/bin/python

rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},

    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},

    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]

class itemgetter:
    """
    Return a callable object that fetches the given item(s) from its operand.
    After f = itemgetter(2), the call f(r) returns r[2].
    After g = itemgetter(2, 5, 3), the call g(r) returns (r[2], r[5], r[3])
    """
    def __init__(self, item, *items):
        if not items:
            def func(obj):
                return obj[item]    #the object must have __getitem__ implemented.
            self._call = func
        else:
            items = (item,) + items
            def func(obj):
                return tuple(obj[i] for i in items)
            self._call = func

    def __call__(self, obj):
        return self._call(obj)

ass attrgetter:
    """
    Return a callable object that fetches the given attribute(s) from its operand.
    After f = attrgetter('name'), the call f(r) returns r.name.
    After g = attrgetter('name', 'date'), the call g(r) returns (r.name, r.date).
    After h = attrgetter('name.first', 'name.last'), the call h(r) returns
    (r.name.first, r.name.last).
    """
    def __init__(self, attr, *attrs):
        if not attrs:
            if not isinstance(attr, str):
                raise TypeError('attribute name must be a string')
            names = attr.split('.')
            def func(obj):
                for name in names:
                    obj = getattr(obj, name)
                return obj
            self._call = func
        else:
            getters = tuple(map(attrgetter, (attr,) + attrs))
            def func(obj):
                return tuple(getter(obj) for getter in getters)
            self._call = func

    def __call__(self, obj):
        return self._call(obj)


#similar itemgetter.
def getitem(key, *keys):    # keys type : tuple
    if not keys:
        def getvalue(item):
            return item[key]
    else:
        def getvalue(item):
            xkeys = (key,) + keys
            return tuple(item[x] for x in xkeys)

    return getvalue

print (sorted(rows, key=getitem('fname', 'fname','uid')))
