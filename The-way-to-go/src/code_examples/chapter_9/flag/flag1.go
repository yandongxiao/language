package main

import (
	"flag"
)

/* loglevel is a pointer to int */
var loglevel = flag.Int("loglevel", 1, "the log level")

func main() {
	flag.Parse()
	println("loglevel =", *loglevel)
}
