package main

const BOOLEAN = true

// just an number, you can use it with other type of variables.
const INT int32 = 10

const INT2 = 1000000000000000000000000000000000000000000000000000

const STRING = "nihao"

func test1() {
	const DD = 128 /* It will say error: DD overflow int8 */
	var num int16 = -1
	println(num + DD)
}

func test(a, b int) (c int, d string) {
	c = a + b
	return
}

func init() {

}

func main() {
	println(BOOLEAN)
	println(INT)
	println(STRING)

	test1()
	//	fmt.Println(DD) /* undefined DD */
}
