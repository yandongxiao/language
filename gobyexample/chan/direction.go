package main

func main() {
	ch1 := make(chan string)
	ch2 := make(chan string)

	// only send message
	go func(sender chan<- string) {
		sender <- "helloworld"
	}(ch1)

	// ch1 only receive messsage, <-在chan的左边就是receive
	// ch2 only send message, <-在chan的右边就是send
	go func(receiver <-chan string, sender chan<- string) {
		msg := <-receiver
		sender <- msg
	}(ch1, ch2)

	println(<-ch2)
}
