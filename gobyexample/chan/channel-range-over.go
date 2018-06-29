package main

func main() {
	chMsg := make(chan string, 2)
	chMsg <- "hello"
	chMsg <- "world"
	close(chMsg)

	for msg := range chMsg {
		println(msg)
	}
}
