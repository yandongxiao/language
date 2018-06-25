package main

import "os/user"
import "fmt"

func main() {
	fmt.Println(user.Current())
}
