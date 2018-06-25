package main

import "unsafe"
import "fmt"

func main() {
	var v byte = 'a'
	fmt.Printf("%c, %v\n", v, v)
	fmt.Println(v, unsafe.Sizeof(v))

	var vv rune = '言'
	fmt.Printf("%c, %v\n", vv, vv)
	fmt.Println(vv, unsafe.Sizeof(vv))
}
