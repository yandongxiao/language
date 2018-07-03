package main

import "fmt"
import "bufio"
import "os"
import "io"

func main() {
	var reader io.Reader
	reader, _ = os.Open("/tmp/data")
	scanner := bufio.NewScanner(reader) /* NOTE this */

	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}

	if scanner.Err() != nil {
		fmt.Println("has read to the end")
	}
}
