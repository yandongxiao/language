package main

import "time"

func recv(ch chan int) {
	i := 0
	for ; i < 10; i++ {
		<-ch
	}
	println(i)
}

func send(ch chan int) {
	for i := 0; i < 30; i++ {
		ch <- i
	}
}

func main() {
	ch := make(chan int)
	go send(ch)
	go recv(ch)
	go recv(ch)
	go recv(ch)

	time.Sleep(time.Second)
}
