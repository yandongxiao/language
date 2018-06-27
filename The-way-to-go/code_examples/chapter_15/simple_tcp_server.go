/**
 * Simple multi-thread/multi-core TCP server.
 * 1. conn.Wriet如果只是写了部分数据，是否会产生error： 猜想应该是不会的
 * 所以，如果只是写了部分数据，上层应用是要负责继续传递后续的数据
 * 在TCP层写应用的话就是存在上面这么个窘境，在http层利用net/http进行IO操作的时候就不存在这个问题
 *
 * 2. panic会将整个程序崩溃掉，不过http包在背后调用了recover函数，使得panic不会影响其它协程
 *
 * 3. 读取数据时可能会存在err==nil, readlength==0的情况吗？ 注意也是有可能的，虽然我不清楚是在什么情况下
 */
package main

import (
	"flag"
	"fmt"
	"net"
	"syscall"
)

const maxRead = 25

func main() {
	flag.Parse()

	if flag.NArg() != 2 {
		panic("usage: host port")
	}
	hostAndPort := fmt.Sprintf("%s:%s", flag.Arg(0), flag.Arg(1))
	listener := initServer(hostAndPort)
	for {
		conn, err := listener.Accept()
		checkError(err, "Accept: ")
		go connectionHandler(conn)
	}
}

func initServer(hostAndPort string) *net.TCPListener {
	serverAddr, err := net.ResolveTCPAddr("tcp", hostAndPort)
	checkError(err, "Resolving address:port failed: `"+hostAndPort+"'")
	listener, err := net.ListenTCP("tcp", serverAddr)
	checkError(err, "ListenTCP: ")
	println("Listening to:    ", listener.Addr().String())
	return listener
}

func connectionHandler(conn net.Conn) {
	connFrom := conn.RemoteAddr().String()
	println("Connection from: ", connFrom)
	sayHello(conn)
	for {
		var ibuf []byte = make([]byte, maxRead+1)
		length, err := conn.Read(ibuf[0:maxRead]) // 假如发送端直接关闭连接，那么err值将不为nil
		ibuf[maxRead] = 0                         // 看程序是如何做到防御性编程的, 0并非是特殊字符, 必须于客户端约定好0是特殊字符才行
		switch err {                              // 用switch对error检查也是一个非常好的方法
		case nil:
			handleMsg(length, err, ibuf)
		case syscall.EAGAIN: // try again, 网络IO是可中断的
			continue
		default:
			goto DISCONNECT //goto语句的应用场景之一
		}
	}

DISCONNECT:
	err := conn.Close()
	println("Closed connection: ", connFrom)
	checkError(err, "Close: ")
}

func sayHello(to net.Conn) {
	obuf := []byte{'L', 'e', 't', '\'', 's', ' ', 'G', 'O', '!', '\n'}
	wrote, err := to.Write(obuf)
	checkError(err, "Write: wrote "+string(wrote)+" bytes.")
}

func handleMsg(length int, err error, msg []byte) {
	if length > 0 { //什么情况下，才能读取的数据为零呢？发送端没有发送任何数据，然后直接关闭连接
		print("<", length, ":")
		for i := 0; ; i++ { //为什么又不以length长度作为循环退出的依据呢？
			if msg[i] == 0 {
				break
			}
			fmt.Printf("%c", msg[i])
		}
		print(">")
	}
}

func checkError(error error, info string) {
	if error != nil {
		panic("ERROR: " + info + " " + error.Error()) // terminate program
	}
}
