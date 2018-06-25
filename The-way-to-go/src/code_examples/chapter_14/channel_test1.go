package main

import "time"

func main() {
	ch := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			println("channel1:", <-ch)
		}
	}()

	go func() {
		for i := 0; i < 10; i++ {
			println("channel2:", <-ch)
		}
	}()

	go func() {
		for i := 0; i < 10; i++ {
			println("channel3:", <-ch)
		}
	}()

	go func() {
		for i := 0; i < 30; i++ {
			ch <- i
		}
	}()

	time.Sleep(3e9)
}
