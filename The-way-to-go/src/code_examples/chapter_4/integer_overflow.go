package main

func main() {
	// var num int8 = 1000000000000000000	/* compile error */

	var num1 int8 = 100
	var num2 int8 = 100
	println(num1 + num2) /* do overflow, but not runtime error */
}
