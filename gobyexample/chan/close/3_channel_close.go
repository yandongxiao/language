package main

func main() {
	chMsg := make(chan string)
	chEnd := make(chan bool)

	go func() {
		for {

			// It will also set ok to false for a closed channel
			msg, more := <-chMsg
			if more {
				println("receive message", msg)
			} else {
				println("have received all messages")
				break
			}
		}
		chEnd <- true
	}()

	for i := 0; i < 3; i++ {
		chMsg <- string(i)
	}
	close(chMsg)

	<-chEnd
}
