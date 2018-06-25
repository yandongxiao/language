package main

type INT int

func main() {
	num1 := 10
	num2 := 1.2
	var num3 INT = 30
	println(num1 + int(num2))

	println(num1 + int(num3)) /* must cast */
}
