package main

import "sort"
import "fmt"

func main() {
	ch := make(chan bool)

	doSort := func(data []int) {
		sort.Ints(data)
		ch <- true
	}

	data := []int{321, 3213, 21, 321, 3, 21, 3, 213, 21, 321}
	go doSort(data[:5])
	go doSort(data[5:])

	<-ch
	<-ch

	fmt.Println(data)
}
