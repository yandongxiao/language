package main

func main() {
	chMsg := make(chan string)
	chEnd := make(chan bool)

	go func() {
		for {
			// It will also set more to false for a closed channel
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

	// 如果不执行close操作，那么主协程因为receive chEnd而阻塞，而另一个协程也因等待receive chMsg而阻塞，死锁
	close(chMsg)

	<-chEnd
}
