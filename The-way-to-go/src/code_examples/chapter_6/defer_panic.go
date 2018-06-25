package main

func main() {
	defer println("hello") /* OK */
	panic("error")
}
