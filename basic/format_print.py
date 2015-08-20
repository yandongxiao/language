#! /usr/bin/python
import math # for range

# do not print new line.
print("It is line with out new line.", end="")
print("")

# print a list, tuple, dict onw time.
nums=[1,2,3,4,5]
mydict = {1:"a", 2:"b"}
print(nums)
print(mydict)
print(3)

# print seprator. note the sep is useless.
print(nums, sep=': ')
print("%d %d %d" % (nums[0], nums[1], nums[2]), sep=": ")

# left align print
print("float number\t %6.3f" % 3.33333)
print("integer number\t %6d " % 20)
print("%-20s:" % "integer number")

# right align print. it is the default behavior.
print("float number %10.3f" % 3.33333)

