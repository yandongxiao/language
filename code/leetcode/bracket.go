package main

func isValid(s string) bool {
	chs := make([]byte, 0, len(s))
	size := len(s)
	for i := 0; i < size; i++ {
		x := s[i]
		if x == '(' || x == '{' || x == '[' {
			chs = append(chs, x)
		} else {
			if len(chs) == 0 {
				return false
			}
			ch := chs[len(chs)-1]
			if (x == ')' && ch == '(') || (x == ']' && ch == '[') || (x == '}' && ch == '{') {
				chs = chs[:len(chs)-1]
			} else {
				return false
			}
		}
	}
	if len(chs) == 0 {
		return true
	}
	return false
}

func main() {
	println(isValid("()"))
	println(isValid("()[]{}"))
	println(isValid("([)])"))
	println(isValid("(]"))
	println(isValid("{[]}"))
}
