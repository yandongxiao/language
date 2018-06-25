package main

import "fmt"
import "strconv"
import "time"

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

	ch := make(chan ST, 1)
	go func() {
		time.Sleep(time.Second)
		fmt.Println(<-ch)
	}()

	ch <- s1
	s1.num = 100
	*s1.data = 200
	time.Sleep(10 * time.Second)
}
