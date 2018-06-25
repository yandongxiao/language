package main

import "fmt"
import "os"
import "bufio"

func main() {
	reader, _ := os.Open("/tmp/data")
	bufreader := bufio.NewReader(reader)

	/* bufreader read more data than 1, and buffer it */
	data, err := bufreader.ReadByte()
	if err != nil {
		panic(err)
	}
	fmt.Println(string(data))

	fmt.Println("Buffered :", bufreader.Buffered())
	fmt.Println("Discard one data")
	bufreader.Discard(1)

	data, err = (bufreader.ReadByte())
	fmt.Println(string(data))
}
