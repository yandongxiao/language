package main

import "fmt"

type Person struct {
	name string
	age  int
}

// golang不允许有方法名重载
func (p Person) getName1() string {
	return "object"
}

func (p *Person) getName2() string {
	return "pointer"
}

func (p Person) setName1(name string) {
	p.name = name
}

func (p *Person) setName2(name string) {
	p.name = name
}

func main() {
	p := Person{"jack", 10}
	// Go automatically handles conversion between values and pointers for method calls.
	println(p.getName1())
	println(p.getName2())
	println((&p).getName1())
	println((&p).getName2())

	// You may want to use a pointer receiver type to avoid copying on method calls
	// or to allow the method to mutate the receiving struct.
	p.setName1("value")
	fmt.Println(p)
	(&p).setName1("value") // 不起作用。method本质上是函数，receiver也是通过参数的形式传递的!!
	fmt.Println(p)
	p.setName2("pointer")
	fmt.Println(p)
}
