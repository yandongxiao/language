#!/usr/bin/env python
# encoding: utf-8

from collections import Counter

c = Counter("abcdsa")
print c.most_common(2)

c = Counter(cat=2, dog=3, tiger=1)
print c.most_common(2)

c = Counter({"cat":2, "dog":3, "tiger":1})
print c.most_common(2)
