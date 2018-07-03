package main

func main() {
	// 1. string的底层指针是没有办法获取的
	// 2. data 和 修改后的bd 肯定没有指向同一块内存。
	// 如果某个函数返回值是string，大可放心使用，就像使用整型一样.
	// string is immutable
	data := "hello world"
	bd := []byte(data)
	bd[0] = 'H'
	println(string(bd))
}
