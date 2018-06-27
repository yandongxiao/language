package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan string)

	go sendData(ch)
	go getData(ch)

	time.Sleep(10 * 1e9)
}

func sendData(ch chan string) {
	ch <- "Washington"
	println("1")
	ch <- "Tripoli"
	println("2")
	ch <- "London"
	println("3")
	ch <- "Beijing"
	println("4")
	ch <- "Tokio"
	println("5")
}

func getData(ch chan string) {
	var input string
	// time.Sleep(1e9)
	for i := 0; i < 5; i++ {
		time.Sleep(1e9)
		input = <-ch
		fmt.Printf("%s\n", input)
	}
}

// Washington Tripoli London Beijing Tokio
