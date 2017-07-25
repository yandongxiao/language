#! /usr/bin/python

from collections import Counter

words = [
'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
'my', 'eyes', "you're", 'under'
]

counter = Counter(words)    # a child of buildins dict
assert counter['eyes'] == 8
assert counter.most_common(3) == [('eyes', 8), ('the', 5), ('look', 4)]  # this is a list.

morewords = ['eyes']
counter.update(morewords)   # keyword iterable.
assert counter['eyes'] == 9

counter1 = Counter(words)   # a child of buildins dict
counter2 = Counter(morewords)

counter = counter1 + counter2
assert 9 == (counter['eyes'])
counter = counter1 - counter2
assert 7 == (counter['eyes'])

counter2 = Counter(["eyes", 'dxyan'])
counter = counter1 + counter2
assert counter['dxyan'] == 1
counter = counter1 - counter2
assert counter['dxyan'] == 0
assert counter['psps'] == 0

