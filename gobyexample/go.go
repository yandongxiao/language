package main

import "time"

func main() {
	go add1(1, 2)
	time.Sleep(time.Second)
}

// 基本语法
func add1(a int, b int) {
	println(a + b)
}
