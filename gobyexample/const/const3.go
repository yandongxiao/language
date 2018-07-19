package main

import "fmt"

func main() {
	// 两个有类型信息的变量无法直接进行计算
	// invalid operation: num1 + num2 (mismatched types int and float64))
	// var num1 int = 10
	// var num2 float64 = 10
	// println(num1 + num2)

	// itoa
	// golang没有显示的enum关键字，使用const+iota进行模拟
	// 1. 每次出现const关键字时，iota被重置为0
	const c0 = iota // c0 == 0
	const c1 = iota // c1 == 0
	// 2. 在下一个const出现之前，每出现一个iota，其代表的数字就会自动增加1
	// 注意c2和c3之间没有逗号
	const (
		c2 = iota // 0
		c3 = iota // 1
	) // 结尾的括号和中括号最好独占一行
	fmt.Println(c0, c1, c2, c3)

	// 如果赋值语句的表达式是一样，那么可以省略后面一个赋值表达式
	// 以上操作只限于常量
	const (
		c00 = iota
		c01
		c02
		c03
	)
	fmt.Println(c00, c01, c02, c03)
}
