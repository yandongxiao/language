#! /usr/bin/python
# Example of faking classes with a closure

import sys
class ClosureInstance:
    def __init__(self, locals=None):
        if locals is None:
            locals = sys._getframe(1).f_locals      # local name space. It is a dict, with name and value in the space.

        # Update instance dictionary with callables
        self.__dict__.update((key,value) for key, value in locals.items()   # __dict__ is special.   if no items, return the key list
                             if callable(value) )   #( ) is a generator
    # Redirect special methods
    def __len__(self):  #this is special.
        print(self.__dict__)
        return self.__dict__['__len__']()

# Example use
def Stack():
    items = []

    def push(item):
        items.append(item)

    def pop():
        return items.pop()      #return the poped value

    def __len__():
        return len(items)

    return ClosureInstance()

if __name__ == '__main__':
    s = Stack()
    print(s)
    s.push(10)
    s.push(20)
    s.push('Hello')
    print(len(s))
    print(s.pop())
    print(s.pop())
    print(s.pop())
