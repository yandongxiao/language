package main

import "fmt"
import "time"

type MSG struct {
	id   int
	name string
}

func handle(ch chan MSG) {
	msg := <-ch
	fmt.Printf("%T, %v\n", msg, msg)
}

func main() {
	ch := make(chan MSG)
	go handle(ch)

	ch <- MSG{1, "hello"}
	time.Sleep(1e9)
}
