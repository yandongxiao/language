package main

import "fmt"

func doit() int {
	return 9
}

func main() {
	//var ch chan int
	ch := make(chan int)
	go func() {
		select {
		case ch <- 1:
			fmt.Println("write to channle")
		}
	}()
	println(<-ch)
}
