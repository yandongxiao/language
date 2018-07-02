package main

import "fmt"
import "os"
import "bufio"

func main() {
	reader, _ := os.Open("/tmp/data")
	bufreader := bufio.NewReader(reader)

	data, _, err := bufreader.ReadLine()
	if err != nil {
		fmt.Println("error: ", err)
		fmt.Println(string(data))
	} else {
		fmt.Println(string(data)) /* Go this way */
	}
}
