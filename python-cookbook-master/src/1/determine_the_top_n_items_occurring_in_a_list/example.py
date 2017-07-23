#!/usr/bin/env python
# encoding: utf-8

"""
    Determine the top-n items occurring in a list
"""

WORDS = [
    'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
    'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
    'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
    'my', 'eyes', "you're", 'under'
]

def doit():
    """ doit """
    # method - 1
    counter = {}
    for word in WORDS:
        if counter.has_key(word):
            counter[word] += 1
        else:
            counter[word] = 1

    sorted_keys = sorted(counter, key=lambda k: counter[k], reverse=True)
    for i in range(0, 3):
        key = sorted_keys[i]
        print key, counter[key]

    # method - 2
    from collections import defaultdict
    counter = defaultdict(int)
    for word in WORDS:
        counter[word] += 1

    for i in range(0, 3):
        key = max(counter, key=lambda k: counter[k])
        print key, counter[key]
        del counter[key]

    # method - 3
    import heapq

    counter = defaultdict(int)
    for word in WORDS:
        counter[word] += 1
    keys = heapq.nlargest(3, counter, key=lambda k: counter[k])
    print [(k, counter[k]) for k in keys]

    # method - 4
    from collections import Counter
    counter = Counter(WORDS)
    print counter.most_common(3)


if __name__ == "__main__":
    doit()
