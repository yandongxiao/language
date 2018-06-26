package main

import (
	"fmt"
	"time"
)

func main() {
	ticker := time.NewTicker(100 * time.Millisecond)
	go func() {
		for now := range ticker.C {
			fmt.Println(now)
		}
	}()

	time.Sleep(time.Second)
	ticker.Stop()
}
