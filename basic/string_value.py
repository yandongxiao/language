#! /usr/bin/python

class Person():
	def __init__(self):
		print("__init__")
	def __repr__(self):
		return "__expr__"

p = Person()
print(p)
a=str(p)
print(a)
