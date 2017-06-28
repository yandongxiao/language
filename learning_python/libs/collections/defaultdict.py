#!/usr/bin/env python
# encoding: utf-8

from collections import defaultdict

dd = defaultdict(list)
dd['name'].append('yan')
dd['name'].append('dx')
dd['name'].append('dx')
dd['age'].append(10)

assert sorted(list(dd.keys())) == ['age', 'name']       # key can be a list.
assert type(dd['name']) == list
assert type(dd['age']) == list

for value in dd.values():
    assert sorted(value) in [["dx", 'dx', 'yan'], [10]]
