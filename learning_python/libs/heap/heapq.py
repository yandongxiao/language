#! /usr/bin/env python3

import heapq    # no class.
l = [5,4,3,2,1]

heapq.heapify(l)
assert l == [1,2,3,5,4]

heapq.heappush(l, 3)
assert l == [1,2,3,5,4,3]


l = list(heapq.merge([1,3,5,7], [0,2,4,8], [5,10,15,20], [], [25]))

assert l == [0, 1, 2, 3, 4, 5, 5, 7, 8, 10, 15, 20, 25]


nl = heapq.nlargest(3, [43,543,312,543,21,31,2])
assert nl == [543, 543, 312]


nl = heapq.nsmallest(3, [43,543,312,543,21,31,2])
assert nl == [2,21,31]

l=[]
heapq.heappush(l, 4)
heapq.heappush(l, 14)
heapq.heappush(l, 8)
heapq.heappush(l, 2)
heapq.heappush(l, 400)
heapq.heappush(l, 90)
assert l == [2,4,8,14,400, 90]      # not sorted.
assert heapq.heappop(l) == 2
assert heapq.heappop(l) == 4
assert heapq.heappop(l) == 8
assert heapq.heappop(l) == 14
assert heapq.heappop(l) == 90
assert heapq.heappop(l) == 400


heapq.heappush(l, (2,"john", 30))
heapq.heappush(l, (1,"jack", 30))
heapq.heappush(l, (2,"big", 30))
heapq.heappush(l, (2,"big", 40))
assert heapq.heappop(l) == (1, "jack", 30)
assert heapq.heappop(l) == (2, "big", 30)
assert heapq.heappop(l) == (2, "big", 40)
assert heapq.heappop(l) == (2, "john", 30)


# how can comparable.
class Test:
    def __init__(self, num, name="jack"):
        self.num = num
    def __ge__(self, ins2): # for >=
        if(self.num >= ins2.num):
            return True
        elif self.num == ins2.num:
            return self.name >= ins2.name
        else:
            return False
    def __gt__(self, ins2): # for >
        return self.num >= ins2.num
    def __lt__(self, ins2): # for >
        return self.num < ins2.num
    def __le__(self, ins2): # for >
        return self.num <= ins2.num

t1 = Test(0)
t2 = Test(1)
assert t2 >= t1
assert t2 > t1
assert t1 <= t2
assert t1 < t2


t1 = Test(0)
t2 = Test(0, "AHA")
assert t2 >= t1
