package main

import "fmt"
import "time"

//import "os"

func worker(i int, ch chan int) {
	sum := 0
	for data := range ch {
		sum += data
	}

	fmt.Println(sum, ": done")
}

func main() {
	ch := make(chan int)

	for i := 0; i < 3; i++ {
		go worker(i, ch)
	}

	for i := 0; i < 1000; i++ {
		ch <- i
	}
	close(ch)

	time.Sleep(100 * time.Second)
}
