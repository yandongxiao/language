package main

import (
	"flag"
	"fmt"
)

var light = flag.Bool("n", false, "turn on the light")
var price = flag.Int("p", 0, "the price")

func main() {
	//	flag.PrintDefaults()
	flag.Parse()

	if *light {
		println("light is specified", *light)
	}

	if *price != 0 {
		println("price", *price)
	}

	fmt.Println(flag.Args())

}
