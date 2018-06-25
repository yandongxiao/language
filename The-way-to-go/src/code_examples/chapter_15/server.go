package main

import (
	"fmt"
	"net"
)

func main() {
	fmt.Println("Starting the server ...")
	// create listener:
	listener, err := net.Listen("tcp", "localhost:50000")
	if err != nil {
		fmt.Println("Error listening", err.Error())
		return // terminate program
	}
	// listen and accept connections from clients:
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting", err.Error())
			return // terminate program
		}
		go doServerStuff(conn)
	}
}

func doServerStuff(conn net.Conn) {
	// 建立的连接为何不需要关闭?
	// 下面的代码需要添加CLose Connection的逻辑
	// 注意：Close操作不是幂等函数，重复调用会导致出错
	for {
		buf := make([]byte, 512)
		_, err := conn.Read(buf)
		if err != nil {
			fmt.Println("Error reading", err.Error())
			err := conn.Close()
			if err != nil {
				fmt.Println("Error Closing", err.Error())
			}
			return // terminate program
		}
		fmt.Printf("Received data: %v", string(buf))
	}
}
