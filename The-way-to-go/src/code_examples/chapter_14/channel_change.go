package main

import "fmt"
import "time"

func main() {
	ch := make(chan *int, 1)
	data := 10

	go func() {
		p := <-ch
		fmt.Println(*p)
	}()
	time.Sleep(1e9)

	ch <- &data
	time.Sleep(1e9)
	data = 999

}
