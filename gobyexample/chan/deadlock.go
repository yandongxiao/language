package main

import "fmt"

func main() {
	// 默认创建的协程是不带缓存的，这导致无论是发送端还是接收端，发送或接收的方式都是阻塞式的.
	// fatal error: all goroutines are asleep - deadlock! 导致唯一的协程也被阻塞了
	// 解决方法：可以创建带缓存的chan
	// chMsg := make(chan string)
	chMsg := make(chan string, 2)
	chMsg <- "hello"
	chMsg <- "world"

	// The close built-in function closes a channel, which must be either bidirectional or send-only. 说明接收端是没有权利close一个chan的
	// any receive from c will succeed without blocking, returning the zero value for the channel element
	close(chMsg)

	fmt.Println(<-chMsg)
	fmt.Println(<-chMsg)
	fmt.Println(<-chMsg) // chan关闭后，每次读取都会成功，且不会被阻塞，返回zero value
}
