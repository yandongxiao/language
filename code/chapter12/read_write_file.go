package main

import (
	"fmt"
	"io/ioutil"
)

func main() {

	data, err := ioutil.ReadFile("/tmp/ddd")
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	err = ioutil.WriteFile("/tmp/ddd.bak", data, 0644)
	if err != nil {
		fmt.Println(err.Error())
		return
	}
}
