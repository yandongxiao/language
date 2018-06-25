package main

import "fmt"
import "bufio"
import "strings"

func main() {
	reader := strings.NewReader("ni hao wo shi")
	scanner := bufio.NewScanner(reader) /* NOTE this */
	scanner.Split(bufio.ScanWords)

	for scanner.Scan() {
		fmt.Println(scanner.Text()) /* by reference */
	}

	if scanner.Err() != nil {
		fmt.Println("has read to the end")
	}
}
