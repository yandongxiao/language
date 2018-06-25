package main

import "fmt"

func check1() (int, error) {
	return 0, nil
}

func check2() (int, error) {
	return 0, fmt.Errorf("failed to check")
}

func shadow() (err error) {
	val, err := check1() // x is created; err is assigned to
	if err != nil {
		return // err correctly returned
	} else {
		fmt.Println(val)
	}

	//err is shadowed during return. luckly, compiler will found the error
	if y, err := check2(); err != nil { // y and inner err are created
		return // inner err shadows outer err so nil is wrongly returned!
	} else {
		fmt.Println(y)
	}
	return
}

func main() {
	err := shadow()
	if err == nil {
		//compiler help us
		fmt.Println("shadow works, note")
	}
}
