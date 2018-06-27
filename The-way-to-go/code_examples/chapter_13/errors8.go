package main

import "fmt"

func guard() {
	if err := recover(); err != nil {
		fmt.Println("error message: ", err)
	}
}

func createpanic() {
	println("begin")
	defer println("defer createpanic")
	panic("try it")
	println("end")
}

func main() {
	defer guard()       //NOTE the location
	createpanic()       /* you'd better put it last */
	println("main end") /* It is not executed */
}
