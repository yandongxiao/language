package main

func main() {
	ch1 := make(chan string)
	ch2 := make(chan string)

	go func() {
		ch1 <- "first"
	}()

	go func() {
		ch2 <- "second"
	}()

	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-ch1:
			println(msg1)
		case msg2 := <-ch2:
			println(msg2) //undefined: msg1
		}
	}
}
