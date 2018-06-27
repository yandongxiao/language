package main

import "fmt"

func test() {
	num := 10
	switch num {
	case 10:
		fallthrough
	case 20:
		println("10, 20") /* multiple line without brace */
	case 30, 40:
		println("30,40") /* OK */
	default:
		println("default")
	}
}

func main() {
	var num1 int = 100

	switch num1 {
	case 98, 99:
		fmt.Println("It's equal to 98")
	case 100:
		fmt.Println("It's equal to 100")
	default:
		fmt.Println("It's not equal to 98 or 100")
	}

	test()
}
