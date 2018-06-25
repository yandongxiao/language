package main

import "fmt"
import "os"
import "bufio"

func main() {
	reader, _ := os.Open("/tmp/data")
	bufreader := bufio.NewReader(reader)

	fmt.Println("Buffered :", bufreader.Buffered())

	data := make([]byte, 100)
	_, err := bufreader.Read(data)
	if err != nil {
		panic(err)
	}
	fmt.Println(string(data))

	fmt.Println("Buffered :", bufreader.Buffered())
}
