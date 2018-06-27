package main

func isPalindrome(x int) bool {
	if x < 0 {
		return false
	} else if x == 0 {
		return true
	}

	old := x
	new := 0
	for x != 0 {
		v := x % 10
		new = 10*new + v
		x = x / 10
	}

	if old == new {
		return true
	}
	return false
}

func main() {
	println(isPalindrome(124))
	println(isPalindrome(121))
}
