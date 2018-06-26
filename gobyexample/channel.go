package main

import "time"

// channels are the pipes that connect concurrent goroutines.
// You can send values into channels from one goroutine and receive those values into another goroutine.
// By default sends and receives block until both the sender and receiver are ready.
// 此种channel可以用来同步两个协程

func delaySend() {
	messages := make(chan int)
	go func(a, b int) {
		time.Sleep(time.Second)
		messages <- a + b
	}(1, 2)

	result := <-messages // 被阻塞
	println("receive done")
	println(result)
}

func delayReceive() {
	messages := make(chan int)
	go func(a, b int) {
		messages <- a + b
		print("send done") // 被阻塞
	}(1, 2)

	time.Sleep(time.Second)
	result := <-messages
	println(result)
}

func main() {
	delaySend()
	delayReceive()

	bufferChan := make(chan string, 2)
	bufferChan <- "hello"
	bufferChan <- "world"
	println(<-bufferChan, <-bufferChan)
}
