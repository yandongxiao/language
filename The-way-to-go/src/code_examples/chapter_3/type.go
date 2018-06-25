package main

import "fmt"

type restable map[int]int

func main () {
	var t restable
	t[1] = 1
	fmt.Println(t)
}
