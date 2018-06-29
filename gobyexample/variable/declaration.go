package main

import "fmt"

func main() {
	// 通过关键字var来声明变量
	// 内置类型
	// NOTICE: 在函数内声明的变量是有初始值的。其它语言是未定义的情况
	var name string    // 初始值为空字符串
	var age int        // 初始值为0
	var salary float64 // 初始值为0
	var sex bool       // 初始值为false

	// 数组和切片
	var friends [10]string // 定义了一个十个元素的数组，元素初始化为空
	var children []string

	// 结构体, 为什么不可以是这种形式
	// var v5 struct {
	//		var age int
	//	}

	var v1 *int // 定义了一个指针，指向nil(NULL)
	var v2 map[string]int
	var v3 func(a int) int

	fmt.Println(name, age, salary, sex, friends, children, v1, v2, v3)

	// 定义一组变量
	var (
		name2   string // 不允许再使用name变量，否则golang会报告重定义错误
		age2    int    // 注意:没有逗号
		salary2 float64
		sex2    bool
	)
	fmt.Println(name2, age2, salary2, sex2)

	// 声明并定义
	// 以下三种方式均可
	var v11 float64 = 10
	var v12 = 10 // Go will infer the type of initialized variables.
	v13 := 10
	fmt.Println(v11, v12, v13)
}
