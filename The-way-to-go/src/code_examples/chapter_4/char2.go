package main

import "unicode"
import "fmt"

func main() {
	var a = 'A' /* the type of a is int32, not int8 or int */
	var b = '\u0041'
	var c = '\u0141'
	fmt.Printf("%c, %c, %c\n", a, b, c)
	fmt.Printf("%T, %T, %T\n", a, b, 6)
	println(unicode.IsLetter(a))
	println(unicode.IsSpace(a))
	println(unicode.IsDigit(a))
}
