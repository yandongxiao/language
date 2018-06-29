package main

import "fmt"

func main() {
	// 这两种类型也是golang的内置类型
	var c1 byte = 'a'
	fmt.Printf("%c", c1)

	var c2 rune = '中'
	fmt.Printf("%c", c2)
}
