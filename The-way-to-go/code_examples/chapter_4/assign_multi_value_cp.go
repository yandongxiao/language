package main

import "fmt"

func test1() {
	a, b, c := 1, 2, 3
	println(a, b, c)
}

func test2() {
	a, b, c := 1, "nihao", true
	println(a, b, c)
}

type MyType struct {
	a int
	b int
}

func test3() {
	a, b := &MyType{1, 2}, 100
	fmt.Println(a, b)
	fmt.Println(a.a, a.b, b)
}

func main() {
	test3()
}
