package main

func main() {
	chMsg := make(chan string)
	chEnd := make(chan bool)

	go func() {
		for {
			msg, more := <-chMsg
			if more {
				println("reveive message", msg)
			} else {
				// receiver会单独收到一条消息，表示已经收到了所有的消息
				println("have received all messages")
				break
			}
		}
		chEnd <- true
	}()

	for i := 0; i < 3; i++ {
		chMsg <- string(i)
	}
	// 发送close消息
	close(chMsg)
	<-chEnd
}
