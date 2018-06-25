package main

import "syscall"
import "fmt"

func main() {
	_, err := syscall.Open("/tmp/aaa", syscall.O_RDONLY, 0644)
	if err != nil {
		//how to get the error num
		fmt.Println(err.Error())
	}
}
