package main

func main() {
	num := 10
	num2 := 1.1

	switch num {
	case 10: /* syntax error: num==10 */
		println(num)
		//	case num2:      /* must match type */
		//		println(num2)
	default:
		println("nihao")
		return
	}

}
