package main

import "math"
import "fmt"

func main() {
	var num int8 = math.MaxInt8
	fmt.Println(num)
	fmt.Println(num + 1)

	var num1 int8 = math.MaxInt8
	var num2 int8 = math.MaxInt8
	var num3 int8 = math.MaxInt8
	fmt.Println(num1 + num2)        /* overflow */
	fmt.Println(num1 + num2 + num3) /* overflow, but not equal 127 */

	fmt.Println(math.MaxInt64)
}
