package main

import "time"
import "fmt"

func main() {
	ch := time.After(time.Second)
	fmt.Println("begin")
	fmt.Println(<-ch)
}
