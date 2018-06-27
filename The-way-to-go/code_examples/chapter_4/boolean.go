package main

func main() {
	b := (1 == 1)
	println(b)

	num1 := 1
	num2 := 2.0
	c := (num1 == int(num2)) /* but num1==2.0 is legal, num1=1.1 is not legal */
	println(c)
}
