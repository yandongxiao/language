package main

import "fmt"

func main() {
	defer func() {
		// r is an empty interface
		if r := recover(); r != nil {
			fmt.Println(r)
		}
	}()

	panic("hello")
	// 一旦发生错误，这个发生panic的函数的后面的语句不再会被执行
	println("world") // unreachable code
}
