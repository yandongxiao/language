package main

import "fmt"

// 既然是predeclared identifiers，那么我们可以定义重名的identifier，隐藏predeclared identifiers
func main() {
	int := 10
	fmt.Println(int)
}
