package main

import "os"
import "fmt"
import "time"

func errcheck(err error) {
	if err != nil {
		panic(err)
	}
}

func input(in *os.File) {
	buf := make([]byte, 1)
	_, err := in.Read(buf)
	if err != nil {
		panic(err)
	}
	fmt.Println(string(buf))
}

func main() {
	in, out, err := os.Pipe()
	errcheck(err)

	out.Close()
	input(in) /* The error is EOF, not ErrClosedPipe */
	time.Sleep(5e9)
}
