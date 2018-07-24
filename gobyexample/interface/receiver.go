package main

type Adder interface {
	add(v int)
	get() int
}

type Person struct {
	age int
}

func (p Person) add(v int) {
	p.age += v
}

func (p Person) get() int {
	return p.age
}

func main() {
	var p Person
	adder := Adder(p)
	adder.add(1)
	println(adder.get()) // not 1
}
