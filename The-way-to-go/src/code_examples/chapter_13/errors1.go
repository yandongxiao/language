package main

import (
	"errors"
	"fmt"
)

func hasError1() (int, error) { // error is an interface
	return -1, errors.New("not match")
}

/*
func hasError2() (int, error) { // error is an interface
	return -1, errors.New(1)    // not illegal
}
*/

func main() {
	if _, err := hasError1(); err != nil {
		fmt.Println(err)
		fmt.Println(err.Error())
		fmt.Printf("error type : %T\n", err)
		return
	}
	/*
		if _, err := hasError2(); err != nil {
			fmt.Println(err)
			fmt.Println(err.Error())
			fmt.Printf("error type : %T\n", err)
			return
		}
	*/
}
