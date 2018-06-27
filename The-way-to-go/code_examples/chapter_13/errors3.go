package main

import "fmt"

/*define you own error */
type PathError struct {
	age  string
	name string
}

/* like Sting */
func (err *PathError) Error() string {
	return err.age + " " + err.name
}

func NewPathError() error {
	return &PathError{"122", "ydx"}
}

func main() {
	if err := NewPathError(); err != nil {
		fmt.Println(err)
	}
}
