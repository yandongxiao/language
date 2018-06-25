package main

import "flag"
import "fmt"

var (
	loglevel int
	debug    bool
)

func init() {
	flag.IntVar(&loglevel, "loglevel", 1, "the log level")
	flag.BoolVar(&debug, "debug", false, "the debug")
}

func main() {
	fmt.Println(flag.CommandLine)
	flag.Usage()
	flag.Parse()
	fmt.Println(flag.CommandLine)
	flag.Usage()

	flag.PrintDefaults()
}
