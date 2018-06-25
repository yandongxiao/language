// nexter.go
package main

import (
	"fmt"
)

type nexter interface {
	next() byte
}

type generator struct{}

func (generator) next() byte {
	return 1
}

func nextFew1(n nexter, num int) []byte {
	//b := new([100]byte)[:] //too ugly
	b := make([]byte, 100)
	for i := 0; i < num; i++ {
		b[i] = n.next()
	}
	return b
}

func main() {
	var gen generator
	fmt.Println("Hello World!", nextFew1(gen, 10))
}
