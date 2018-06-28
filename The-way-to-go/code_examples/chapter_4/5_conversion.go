package main

import "fmt"

func main() {
	type INTS []int
	var a INTS = INTS{10}
	var b = []int{20}
	a = b // 这里又不是必须的
	b = a
	fmt.Println(a, b)

	type INT int
	var x INT = 10
	var y = 20
	x = INT(y) // 这里的强制类型转换是必须的
	y = int(x)
	fmt.Println(x, y)
}
