package main

import "fmt"

type ST struct {
	name string
	age  int
}

func main() {
	age := 10
	name := "ads"

	fmt.Printf("%v, %v\n", age, name)

	s := ST{name, age} /* useful for struct */
	fmt.Printf("%+v\n", s)

	fmt.Printf("%#v\n", s) /* the literal format */
}
