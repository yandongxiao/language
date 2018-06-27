package main

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
