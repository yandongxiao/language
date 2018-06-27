// nexter.go
package main

import (
	"fmt"
)

type nexter interface {
	next() byte
}

func nextFew1(n nexter, num int) []byte {
	b := make([]byte, 10)
	for i := 0; i < num; i++ {
		b[i] = n.next()
	}
	return b
}

/* never use a pointer to an interface type, this is already a pointer! */
func nextFew2(n *nexter, num int) []byte {
	b := make([]byte, 10)
	for i := 0; i < num; i++ {
		b[i] = (*n).next() // compile error:  n.next undefined (type *nexter has no field or method next)
	}
	return b
}

type ST struct {
}

func (ST) next() byte {
	return 'v'
}

/* never use a pointer to an interface type, this is already a pointer! */
func main() {
	fmt.Println(string(nextFew1(ST{}, 5)))
	fmt.Println(string(nextFew1(&ST{}, 5)))

	inter := new(nexter)
	*inter = ST{}
	fmt.Println(string(nextFew2(inter, 5)))
}
