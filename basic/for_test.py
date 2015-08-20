#! /usr/bin/python
#you must not forget the "!"

import math     # for range

for x in [1,2,3,4,5,6,7,8,9,10] :
    print("%d" % x, end=" ")
print("")

for x in range(1, 10 + 1) : # 10 is not inlude in (1, 10).
    print("%d" % x, end=" ")
print("")

nums = [2*x for x in range(1, 10 + 1) if x%2==0 ]
for x in nums :
    print("%d" % x, end=" ")
print("")

