package main

import "fmt"

func test() (int, int) {
	return 1, 2
}

func main() {
	fmt.Println(test())
}
