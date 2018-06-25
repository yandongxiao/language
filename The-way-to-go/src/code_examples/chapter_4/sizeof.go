package main

import "unsafe"

func main() {
	v1 := true
	v2 := 10
	println(unsafe.Sizeof(v1))
	println(unsafe.Sizeof(v2))
}
