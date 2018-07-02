package main

import "fmt"
import "io/ioutil"

func main() {
	fmt.Println(ioutil.Discard.Write([]byte("helloworld")))
}
