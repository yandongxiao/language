package main

import "fmt"

func main() {
	// test integer
	var num1 = 1 // 等价于var num1 int = 1, 等价于 num1 := 1
	var num2 = 2
	fmt.Println(num1 + num2)

	// test float
	// invalid operation: f1 + f2 (mismatched types int and float64))
	f1 := 1 // 常量是没有类型的, 所以var f1 int8 = 1也是被允许的
	f2 := 1.6
	fmt.Println(f1 + int(f2)) // 向下取整

	// test string
	s1 := "hello"
	s2 := "world"
	fmt.Println(s1 + s2)
}
