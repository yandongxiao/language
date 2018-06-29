package main

// only send message
func ping(ch chan<- string) {
	ch <- "helloworld"
}

// ch1 only receive messsage
// ch2 only send message
func pong(ch1 <-chan string, ch2 chan<- string) {
	msg := <-ch1
	ch2 <- msg
}

func main() {
	ch1 := make(chan string)
	ch2 := make(chan string)

	go ping(ch1)
	go pong(ch1, ch2)
	println(<-ch2)
}
