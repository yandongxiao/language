#!/usr/bin/env python
# encoding: utf-8

words = [
   'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
   'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
   'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
   'my', 'eyes', "you're", 'under', 'into', 1, 1, 1, 1
]

# 对一个sequence做统计工作
from collections import Counter

word_counter = Counter(words)

# 返回的是List， List是可以直接打印的
#for name, count in word_counter.most_common(3):
#    print name, count
print word_counter.most_common(3)


morewords = ['why','are','you','not','looking','in','my','eyes']
word_counter.update(morewords)
# 如果不同的key拥有相同的计数，则比较它们的key
print word_counter.most_common(3)

print word_counter["into"]
