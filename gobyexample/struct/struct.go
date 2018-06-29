package main

import "fmt"

// 类名称也不一定要大写
// Omitted fields will be zero-valued.
type person struct {
	name string
	age  int
}

// 无论是指针还是变量本身，统一采用.的方式
// You can also use dots with struct pointers - the pointers are automatically dereferenced
func foo(p *person) {
	println(p.name)
}

func main() {
	p1 := person{"jack", 10}
	fmt.Println(p1) // 打印出具体内容

	// 值传递
	p2 := p1
	p2.age = 100
	fmt.Println(p1, p2)

	foo(p1)
}
