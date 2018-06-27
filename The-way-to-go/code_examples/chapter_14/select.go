package main

import "fmt"
import "time"

func myroutine(val int, ch chan int) {
	for {
		time.Sleep(time.Second)
		ch <- val
	}
}

const MAXCHANNELS = 10

func main() {
	channels := make([]chan int, MAXCHANNELS)
	for i := 0; i < MAXCHANNELS; i++ {
		channels[i] = make(chan int)
		go myroutine(i, channels[i])
	}

	for {
		var val int
		select {
		case val = <-channels[0]:
			fmt.Println(val)
		case val = <-channels[1]:
			fmt.Println(val)
		}
	}
}
