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
		fmt.Println(string(scanner.Bytes())) /* by value */
		fmt.Println(scanner.Text())          /* by reference */
	}

	if scanner.Err() != nil {
		fmt.Println("has read to the end")
	}
}
