package main

import "strconv"

func ttt(s string) string {
	v, _ := strconv.ParseInt(s, 10, 64)
	println(v)
	return strconv.FormatInt(v*2, 'v', 2, 32)
}

func main() {
	println(ttt("100"))
}
