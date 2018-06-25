package main

import "fmt"
import "errors"

func main() {
	fmt.Println(test())
}

func test() (val int, err error) {
	return -1, errors.New("nihao")
}
