package main

import "fmt"

func doerror() error {
	return fmt.Errorf("%d, %s", 1, "ad")
}

func main() {
	err := doerror()
	fmt.Println(err)
	fmt.Printf("%T\n", err)
}
