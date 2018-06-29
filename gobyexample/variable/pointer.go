package main

// 竟然返回了一个栈变量的地址？
func ttt() *int {
	num := 10
	println(&num)
	return &num
}

func main() {
	p := ttt()
	*p = 100 * 100 /* the value of pointer is not changed */
	println(p, *p)
}
