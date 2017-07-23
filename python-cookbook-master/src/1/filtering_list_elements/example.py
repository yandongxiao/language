#!/usr/bin/env python
# encoding: utf-8

def doit():
    """ doit """
    mylist = [1, 4, -5, 10, -7, 2, 3, -1]

    # All positive values
    print [elmt for elmt in mylist if elmt > 0]

    # All negative values
    print [elmt for elmt in mylist if elmt < 0]

    # Negative values clipped to 0
    print [elmt if elmt > 0 else 0 for elmt in mylist]

    # Positive values clipped to 0
    print [elmt if elmt < 0 else 0 for elmt in mylist]

    # generator
    print min(elmt if elmt < 0 else 0 for elmt in mylist)


    # Compressing example
    addresses = [
        '5412 N CLARK',
        '5148 N CLARK',
        '5800 E 58TH',
        '2122 N CLARK',
        '5645 N RAVENSWOOD',
        '1060 W ADDISON',
        '4801 N BROADWAY',
        '1039 W GRANVILLE',
    ]

    counts = [0, 3, 10, 4, 1, 7, 6, 1]

    # method - 1
    print [x for x, y in zip(addresses, counts) if y > 5]

    # method - 2
    indexs = (i for i, c in enumerate(counts) if c > 5)
    print [addresses[i] for i in indexs]

    # method - 3
    from itertools import compress
    selector = [x > 5 for x in counts]
    print list(compress(addresses, selector))

if __name__ == "__main__":
    doit()
