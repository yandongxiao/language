#! /usr/bin/python

records = [
     ('foo', 1, 2),
     ('bar', 'hello'),
     ('foo', 3, 4),
]

def ddd(m, **n):
	print(m)
	print(n)

def fff(m, *n):
	print(m)
	print(n)

for m, *n in records:
	print(m)
	print(n)

fff("dsal", *(1,2,3,4))

fff("dsal", *[1,2,3,4])

#ddd("dsal", 1=2,3=4)	?

