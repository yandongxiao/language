package main

import "fmt"
import "sync"

var wg sync.WaitGroup // 1

func routine(i int) {
	defer wg.Done() // 3
	fmt.Printf("routine %v finished\n", i)
}

func main() {
	for i := 0; i < 10; i++ {
		wg.Add(1)     // 2
		go routine(i) // *
	}
	wg.Wait() // 4
	fmt.Println("main finished")
}
