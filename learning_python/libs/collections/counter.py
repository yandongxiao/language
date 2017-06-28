#!/usr/bin/env python
# encoding: utf-8

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
