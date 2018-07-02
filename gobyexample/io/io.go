package main

import "flag"
import "fmt"

func main() {
	fmt.Println(flag.Args()) /* some wierd */
	args := flag.Args()
	for str := range args {
		fmt.Println(str)
	}
}
