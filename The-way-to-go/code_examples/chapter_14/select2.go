package main

func doit() *int {
	data := new(int)
	*data = 10
	return data
}

func main() {
	//var ch chan int
	ch := make(chan *int) /* how do you handle it in different process ? */
	go func() {
		select {
		case ch <- doit():
		}
	}()
	println(*(<-ch))
}
