package main

import "fmt"
import "os"
import "bufio"

func main() {
	reader, _ := os.Open("/tmp/data")
	bufreader := bufio.NewReader(reader)

	data, err := bufreader.ReadBytes('A')
	if err != nil {
		fmt.Println("error: ", err)
		fmt.Println(string(data))
	}
}
