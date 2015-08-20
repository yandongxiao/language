#! /usr/bin/python

a = 20

def aaa():
    a = 10

print("a=", a)  #20
aaa()
print("a=", a)  #20



def gaaa():
    global a
    a = 10

print("a=", a)  #20
gaaa()
print("a=", a)  #10

count = 20

def make_counter():
    count = 0
    def counter():
        nonlocal count
        count += 1
        return count
    return counter
    
def make_counter_test():
  mc = make_counter()
  print(mc())
  print(mc())
  print(mc())

make_counter_test();


