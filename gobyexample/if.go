package main

import "fmt"

func main() {

	// golang不支持三目运算符: ternary if
	if 8%4 == 0 {
		println("if语句的基本用法, 条件两边的括号可以省，大括号不能省")
	}

	// A statement can precede conditionals; any variables declared in this statement are available in all branches
	if num := 1; num < 0 {
		fmt.Printf("%d is negtive", num)
	} else if num == 0 {
		fmt.Printf("%d is zero", num)
	} else {
		fmt.Printf("%d is positive", num)
	}

	// non-bool val (type int) used as if condition)
	val := 10
	if val {
		println("val")
	}
}
