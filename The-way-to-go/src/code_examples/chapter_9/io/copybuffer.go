package main

import "os"
import "fmt"
import "io"

func errCheck(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	var src *os.File
	var dest *os.File
	var err error

	src, err = os.Open("/tmp/data")
	errCheck(err)
	defer src.Close()

	dest, err = os.Create("/tmp/data.cp")
	errCheck(err)
	defer dest.Close()

	size, err := io.CopyBuffer(dest, src, nil)
	errCheck(err)
	fmt.Println("size =", size)

}
