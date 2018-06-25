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

	size, err := io.CopyN(dest, src, 100) /* if file length < 100, err EOF */
	errCheck(err)
	fmt.Println("size =", size)

}
