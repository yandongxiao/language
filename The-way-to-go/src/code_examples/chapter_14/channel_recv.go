package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int)
	go func(ch chan<- int) {
		for i := 0; i < 10; i++ {
			ch <- i
		}
		close(ch)
	}(ch)

	go func(ch <-chan int) {
		for v := range ch {
			fmt.Println(v)
		}
	}(ch)

	time.Sleep(1 * time.Second)

	_, ok := <-ch
	fmt.Printf("%T:%v\n", ok, ok)
}
