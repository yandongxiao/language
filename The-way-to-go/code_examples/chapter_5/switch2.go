package main

import "fmt"

func test() {
	var num1 int = 7
	if num1 < 0 {
		fmt.Println("Number is negative")
	} else if num1 > 0 && num1 < 10 {
		fmt.Println("Number is between 0 and 10")
	} else {
		fmt.Println("Number is 10 or greater")
	}

}

func main() {
	var num1 int = 7

	switch {
	case num1 < 0:
		fmt.Println("Number is negative")
	case num1 > 0 && num1 < 10:
		fmt.Println("Number is between 0 and 10")
	default:
		fmt.Println("Number is 10 or greater")
	}

	test()
}
