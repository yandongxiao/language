package main

import "fmt"
import "time"

func send1(ch chan int) {
	for i := 0; i < 100; i++ {
		time.Sleep(time.Second)
		ch <- i /* how to handle the panic, normally, send2 should not close the channel */
	}
}

func send2(ch chan int) {
	for i := 0; i < 100; i++ {
		ch <- i
	}
	close(ch)
}

func recv(ch chan int) {
	for x := range ch {
		fmt.Println(x)
	}
	close(ch)
}

func main() {
	ch := make(chan int)
	go send1(ch)
	go send2(ch)
	go recv(ch)

	time.Sleep(100 * time.Second)
}
