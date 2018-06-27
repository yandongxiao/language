package main

import (
	"time"
)

func main() {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop() //Stop the ticker

	for {
		select {
		case <-ticker.C:
			println("a message")
		}
	}
}
