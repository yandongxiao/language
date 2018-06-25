//word_letter_counter.go
//等待用户的输入，直到用户输入'S'字符，代表输入结束
//统计以下结果：
//  1. 字符个数，‘\r’ '\n' 除外
//  2. words个数
//  3. 行数
//注意：只需要考虑ASCII字符即可

package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"strings"

	"github.com/golang/glog"
)

func parse(input string) (numLine, numWord, numChar int, err error) {
	if input == "" {
		return
	}

	input = strings.Replace(input, "\r", "", -1)
	input = strings.Replace(input, "	", " ", -1)

	lines := strings.Split(input, "\n")
	numLine = len(lines)

	for _, line := range lines {
		if line == "" {
			break
		}
		words := strings.Split(line, " ")
		for _, word := range words {
			if word != "" {
				numWord += 1
			}
			numChar += len(word)
		}
	}
	return
}

func parse2(input string) (numLine, numWord, numChar int, err error) {
	charReader := bufio.NewReader(strings.NewReader(input))
	empty := true

	for {
		var char byte
		char, err = charReader.ReadByte()
		if err != nil {
			if err == io.EOF {
				err = nil
				break
			} else {
				glog.Fatalln("读取字符失败")
				return
			}
		}

		empty = false

		switch char {
		case '\r':
			break
		case '\n':
			numLine += 1
			numWord += 1
		case '\t', ' ':
			numWord += 1
		default:
			numChar += 1
		}
	}

	if !empty {
		numLine += 1
		if input[len(input)-1] != '\n' {
			numWord += 1
		}
	}

	return
}

func main() {

	flag.Parse()

	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('S')
	if err != nil {
		glog.Errorln("读取用户输入数据失败")
		return
	}
	numLine, numWord, numChar, err := parse(input)

	if err != nil {
		glog.Infoln("work failed")
	}

	fmt.Println("number of lines: ", numLine)
	fmt.Println("number of words: ", numWord)
	fmt.Println("number of charachater: ", numChar)
}
