// function_parameter.go
package main

import (
	"fmt"
)

func main() {
	println(callback(1, Add))
}

func Add(a, b int) int {
	fmt.Printf("The sum of %d and %d is: %d\n", a, b, a+b)
	return a + b
}

func callback(y int, f func(int, int) int) int {
	return f(y, 2) // this becomes Add(1, 2)
}

// Output:  The sum of 1 and 2 is: 3
