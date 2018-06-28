package main

func lengthOfLastWord(s string) int {
	size := 0
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == ' ' || s[i] == '\t' {
			if size != 0 {
				return size
			}
			continue
		}
		size++
	}
	return size
}

func main() {
	println(lengthOfLastWord("hello "))
	println(lengthOfLastWord(""))
	println(lengthOfLastWord("hello world"))
}
