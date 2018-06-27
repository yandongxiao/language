package main

import "fmt"

func test() func(int) int {
	return func(num int) int {
		return num
	}
}

func main() {
	f := test()
	fmt.Println(f(1))
}
