package main

import "fmt"

func main() {
	// for 是golang当中唯一的循环遍历的方式
	// 支持continue 和 break
	for i := 0; i < 10; i++ {
		fmt.Printf("%d, ", i)
	}

	for {
		println("while true")
		break
	}

	i := 1
	for i < 10 {
		fmt.Printf("%d, ", i)
		i++
	}
}
