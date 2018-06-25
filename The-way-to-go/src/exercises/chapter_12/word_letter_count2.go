package main

import (
	"bufio"
	"os"
	"strings"
)

func WordCount(data string) int {
	data = strings.Replace(data, "	", " ", -1)
	data = strings.Trim(data, "\r\n ")
	return strings.Count(data, " ") + 1
}

func CharCount(data string) int {
	return len(data) - 1
}

func main() {
	var lines, words, chars int

	input := bufio.NewReader(os.Stdin)
	for {
		data, err := input.ReadString('\n')
		if err != nil {
			break
		}
		lines++
		words += WordCount(data)
		chars += CharCount(data)
	}

	println("the number of lines :", lines)
	println("the number of words :", words)
	println("the number of characters :", chars)
}
