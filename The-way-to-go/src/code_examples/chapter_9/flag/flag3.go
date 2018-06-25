package main

import "flag"
import "fmt"

var (
	loglevel   int
	debuglevel int
)

func init() {
	flag.IntVar(&loglevel, "loglevel", 1, "the log level")
	flag.IntVar(&debuglevel, "debug", 1, "debug level")
}

func main() {
	/* the option must not be separated by command arguments */
	flag.Parse()
	println("flag.NArg =", flag.NArg())
	fmt.Println("flag.Arg() =", flag.Args())
	println("loglevel =", loglevel)
	println("debug=", debuglevel)
}
