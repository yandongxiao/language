package main

func test1() {}
func test2() {}

func main() {
	//println(test1 == test2)
	//var bb = map[int]int{}
	//var cc = map[int]int{}
	//println(bb == cc)

	//var b = []int{}
	//var c = []int{}
	//println(b == c)

	// 可以比较
	var b = make(chan int)
	var c = b
	println(b == c)

	// [3]int{}是可以比较的，[]int{}是不可以比较的。两者的区别主要是因为[]int是不可以比较的
	// interface的比较规则如下：
	//		1. 首先比较的两个对象必须是同一种类型，即实现了相同的接口
	//		2. 如果底层类型不相同，则返回false
	//		3. 如果底层类型相同，但是类型不支持比较，如map, slice, 则报错
	//		4. 如果支持比较，那么就比较底层类型是否相同。
	var d interface{} = 3
	var e interface{} = map[int]int{}
	println(d == e)

}
