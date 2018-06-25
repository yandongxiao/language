package main

import "time"

func main() {
	ch := make(chan int, 1)
	go func() {
		time.Sleep(time.Second)
		close(ch)
	}()

	go func() {
		ch <- 1
	}()

	time.Sleep(10 * time.Second)
	println(<-ch)
	/*
		for data := range ch {
			println(data)
		}
	*/
}
