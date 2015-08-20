#! /usr/bin/python


def func():
    for x in range(0,10):
        yield x

gen = func()
next(gen)   #0
#print(gen)  # error
print(next(gen))    #1

for x in gen:
    print(x, end=" ")
print("")


#---another gnerator-------

def func2():
    result = yield
    print("result = %d" % result)

handler = func2()
next(handler)   #must call it.
#handler.send(10)    #return 10, and call stopIteration exception.


#----correct------
def func3():
    while(True):
        value = yield
        print("result = %d" % value)
handler = func3()
next(handler)   # it fire the generator, and you can send value to it.
handler.send(10)
handler.send(20)
handler.send(30)



#---keep state test--------
def func4():
    a = 10
    while(True):
        a += 1      #this time a is alwayse 11, if a is in while.
        value = yield
        print("a = {}, and result {}".format(a, value))
handler = func4()
next(handler)   # it fire the generator, and you can send value to it.
handler.send(10)
handler.send(20)
handler.send(30)


