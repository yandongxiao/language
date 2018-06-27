package main

import "fmt"

type PathError struct {
	age  string
	name string
}

func (err *PathError) Error() string {
	return err.age + " " + err.name
}

func doerror() error { /* it is empty interface */
	return &PathError{"122", "ydx"}
}

func main() {
	if err := doerror(); err != nil {
		switch err := err.(type) { /* same as other object */
		case *PathError:
			fmt.Println(err)
			fmt.Println("path error")
		}
	}
}
