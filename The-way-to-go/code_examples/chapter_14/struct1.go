package main

import "fmt"
import "strconv"

type ST struct {
	num  int
	data *int
}

func (s ST) String() string {
	return strconv.Itoa(s.num) + strconv.Itoa(*s.data)
}

func main() {
	data := 100
	s1 := ST{1, &data}
	s2 := ST{2, &data}

	data = 123

	fmt.Println(s1)
	fmt.Println(s2)
}
