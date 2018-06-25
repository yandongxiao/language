package main

import "fmt"

func compose(f, g func(int) int) func(int) int {
	return func(num int) int {
		return g(f(num))
	}
}

func add2(num int) int {
	return num + 2
}

func mult2(num int) int {
	return num * 2
}

func main() {
	fmt.Println(compose(mult2, add2)(10))
	fmt.Println(compose(mult2, add2)(15))
}
