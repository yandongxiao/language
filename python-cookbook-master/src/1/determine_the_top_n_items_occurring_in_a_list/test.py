#!/usr/bin/env python
# encoding: utf-8

def top_3(words):
    counter = {}
    for word in words:
        if counter.has_key(word):
            counter[word] += 1
            continue
        counter[word] = 1

    counter = sorted(zip(counter.values(), counter.keys()), reverse=True)

    i = 1
    for count, name in counter:
        print name, count
        i += 1
        if i > 3:
            break

words = [
   'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
   'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
   'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
   'my', 'eyes', "you're", 'under'
]

top_3(words)

morewords = ['why','are','you','not','looking','in','my','eyes']
# words.extend(morewords)   # words被改变
newwords = words + morewords
top_3(newwords)
