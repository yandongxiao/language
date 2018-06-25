package main

//#cgo LDFLAGS: -L. -ltest1
//extern void sayHi();
import "C"
import "fmt"

func main() {
	a, b := C.sayHi()
	fmt.Println(a, b)
}
