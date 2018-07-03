package main

import "flag"
import "fmt"

var (
	log bool
)

func init() {
	flag.BoolVar(&log, "log", false, "the log level")
}

func main() {
	flag.Parse()
	println("narg == ", flag.NArg())
	fmt.Println("args == ", flag.Args())
	println("log =", log)
}
