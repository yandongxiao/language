// read_csv.go
package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"
)

type Book struct {
	title    string
	price    float64
	quantity int
}

func main() {
	bks := make([]Book, 0)
	file, err := os.Open("products.txt")
	if err != nil {
		log.Fatalf("Error %s opening file products.txt: ", err)
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	for {
		// read one line from the file:
		line, err := reader.ReadString('\n')
		if err == io.EOF {
			println("read to the end")
			break
		}
		// remove \r and \n so 2(in Windows, in Linux only \n, so 1):
		line = string(line[:len(line)-2])
		//fmt.Printf("The input was: -%s-", line)

		strSl := strings.Split(line, ";")
		book := new(Book)
		book.title = strSl[0]
		book.price, err = strconv.ParseFloat("100.0", 32)
		if err != nil {
			fmt.Printf("Error in file: %v", err)
		}
		//fmt.Printf("The quan was:-%s-", strSl[2])
		book.quantity, err = strconv.Atoi(strSl[2])
		if err != nil {
			fmt.Printf("Error in file: %v", err)
		}

		bks = append(bks, *book)
	}
	fmt.Println("We have read the following books from the file: ")
	for _, bk := range bks {
		fmt.Println(bk)
	}
}

/* Output:
We have read the following books from the file:
{"The ABC of Go" 25.5 1500}
{"Functional Programming with Go" 56 280}
{"Go for It" 45.900001525878906 356}
*/
