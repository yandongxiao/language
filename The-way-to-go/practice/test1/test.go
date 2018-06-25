package main

/*
extern void sayHi();
extern int sum(int, int);
*/
import "C"
import "fmt"

func main() {
	C.sayHi()
	a, b := C.sum(C.int(10), C.int(20))
	fmt.Printf("<%d, %T>, <%v, %T>", int(a), a, b, b)
	fmt.Println(C.sum(C.int(10), C.int(20)))
}
