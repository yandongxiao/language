package main

import "fmt"
import "io/ioutil"

func errcheck(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	entries, err := ioutil.ReadFile("/tmp/data")
	errcheck(err)
	fmt.Println(string(entries))
}
