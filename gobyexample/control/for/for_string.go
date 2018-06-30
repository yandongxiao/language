package main

import "fmt"

// Golang的字符串实际上是UTF-8编码的字符串，UTF-8的特点是，有些字符是占一个字节，大多数字符占两个字节，也有字符占三或四个字节；
// len(s) 返回的是字节数。
// We see that Unicode-characters take 2 bytes; some characters can even take 3 or 4 bytes.
// If erroneous UTF-8 is encountered, the character is set to U+FFFD and the index advances by one byte.
// In the same way the conversion c:=[]int(s) is allowed, then each int contains a Unicode code point: every character from the string corresponds to one integer;
// similarly the conversion to runes can be done with r := []rune(s)
// byte 表示一个ASCII字符，rune=int表示任意一个UTF-8编码的字符
func main() {
	s := "\u00ff\u754c"
	for i, c := range s {
		fmt.Printf("%d:%c ", i, c)
	}
}

// prints: 0:ÿ 2:界
