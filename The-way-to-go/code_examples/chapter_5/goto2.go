// compile error goto2.go:8: goto TARGET jumps over declaration of b at goto2.go:8
package main

import "fmt"

func main() {
	a := 1
	b := 9
	goto TARGET // compile error
TARGET:
	b += a
	fmt.Printf("a is %v *** b is %v", a, b)
}
