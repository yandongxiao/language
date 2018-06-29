package main

func main() {
	var num int

	// 这里的分号是必须的，否则整个表达式会当做val进行处理
	switch num = 10; {
	case 1 == 1: // 需要是表达式形式
		println(num)
	default:
		println("not equal")
	}

	switch num = 10; num {
	case 10:
		println("equal")
	default:
		println("not equal")
	}

}
