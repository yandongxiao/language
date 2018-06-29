package main

import "fmt"

func main() {
	var a [5]int
	fmt.Println(a)

	var b = [5]int{1, 2, 3, 4}
	fmt.Println(b)

	// 5和右大括号如果不在同一行，需要在5后面添加逗号
	c := []int{1, 2, 3, 4}
	fmt.Println(c)
}
