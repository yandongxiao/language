package main

import "unsafe"
import "fmt"

/* int is the integer type which offers the fastest processing speeds. */
/* Use float64 whenever possible, because all the functions of the math package expect that type */
func main() {
	num1 := 10
	fmt.Printf("%d\n", unsafe.Sizeof(num1))

	var num2 uint = 100
	fmt.Printf("%d\n", unsafe.Sizeof(num2))
}
