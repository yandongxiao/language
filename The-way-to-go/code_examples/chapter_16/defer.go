package main

import "fmt"

func defer1() {
	val1 := 0
	for ; val1 < 10; val1++ {
		defer fmt.Println(val1)
	}
}

type ST struct {
	num int
}

/* there is different between *ST and ST*/
func (s *ST) call() {
	fmt.Println(s.num)
}

func defer2() {
	st := ST{}
	for i := 0; i < 10; i++ {
		defer st.call()
		st.num++
	}
}

func defer3() {
	val1 := 0
	for ; val1 < 10; val1++ {
		defer func() {
			fmt.Println(val1)
		}()
	}
}

func main() {
	defer1()
}
