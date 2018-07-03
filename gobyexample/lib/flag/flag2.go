package main

import "flag"

var (
	loglevel int
)

func init() {
	flag.IntVar(&loglevel, "loglevel", 1, "the log level")
}

func main() {
	flag.Parse()

	println("loglevel =", loglevel)
}
