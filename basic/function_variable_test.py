#! /usr/bin/python

def func():
    pass
func()

x=10
def func():
    global x
    l = [x for x in range(5)]
    print(x)    # x=10.
func()


def func():
    x = -1
    l=[x for x in range(5)]
    print(x)    # x=-1
func()

def func():
    a=10
func.a=10
print(func.a)   #10

def func():
    var=10
    def nest1():
        def nest2():
            nonlocal var
            print(var)  #10
        nest2()
    nest1()
func()

def func():
    X=20
    def nest1():
        print(X)    #20
    nest1()
func()

#change the attr
L=[1,2,3]
def func():
    L.append(10)    
func()
print(L)    #[1,2,3,10]

