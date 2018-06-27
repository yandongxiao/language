package main

import (
	"b"
)

/*
 * 1. go install, not go build
 * 2. the b.a is not a standard static library of system, you can not use it in C
 */
func main() {
	b.Printb()
}
