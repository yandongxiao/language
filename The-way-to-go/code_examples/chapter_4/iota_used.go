package main

const (
	V1 = iota
	V2 = iota * 10
	V3 = iota * 10
)

const (
	VV = iota + 100
)

func main() {
	println(V1)
	println(V2) /* 1 */
	println(V3) /* 2 */

	println(VV) /* 100 */
	// num := iota + 1
	// println(num)
}
