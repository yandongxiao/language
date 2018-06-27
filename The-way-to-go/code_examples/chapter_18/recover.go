package main

import "fmt"

func dopanic() (num int) {
	num = 100 /* do not work */
	panic("very panic")
}

func protect() int {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("error happend", err)
		}
	}()

	return dopanic()
}

func main() {
	println(protect())
	println("main end")
}
