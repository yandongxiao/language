package main

type Interface1 interface {
	func1()
}

type Interface2 interface {
	func2()
}

type Interface3 interface {
	Interface1
	Interface2
}

func main() {
	println("helloworld")
}
