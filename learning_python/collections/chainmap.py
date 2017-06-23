#!/usr/bin/env python3
# encoding: utf-8

from collections import ChainMap

class DeepChainMap(ChainMap):
    'Variant of ChainMap that allows direct updates to inner scopes'

    def __delitem__(self, key):
        for mapping in self.maps:
            if key in mapping:
                del mapping[key]
                return
        raise KeyError(key)

    def __setitem__(self, key, val):
        for mapping in self.maps:
            if key in mapping:
                mapping[key] = val
                return
        self.maps[0][key] = val

d = DeepChainMap({'zebra': 'black'}, {'elephant': 'blue'}, {'lion': 'yellow'})
d['lion'] = 'orange'         # update an existing key two levels down
d['snake'] = 'red'           # new keys get added to the topmost dict
del d['elephant']            # remove an existing key one level down
print(d)
