#!/usr/bin/env python
# encoding: utf-8

words = [
   'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
   'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
   'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
   'my', 'eyes', "you're", 'under'
]

# method-1
counter = {}
for word in words:
    if counter.has_key(word):
        counter[word] += 1
    else:
        counter[word] = 1

sorted_keys = sorted(counter, key=lambda k: counter[k], reverse=True)
for i in range(0, 3):
    key = sorted_keys[i]
    print key, counter[key]

# method-2
from collections import defaultdict
counter = defaultdict(int)
for word in words:
    counter[word] += 1

for i in range(0, 3):
    k1 = max(counter, key=lambda k: counter[k])
    print k1, counter[k1]
    del counter[k1]

# method-3
from collections import defaultdict
import heapq

counter = defaultdict(int)
for word in words: counter[word] += 1
keys = heapq.nlargest(3, counter, key=lambda k: counter[k])
print [(k, counter[k]) for k in keys]

# method 4
from collections import Counter
counter = Counter(words)
print counter.most_common(3)
