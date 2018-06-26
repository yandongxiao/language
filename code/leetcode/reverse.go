package main

func reverse(x int) int {
	const MaxInt = 2147483647
	const MinInt = -2147483648
	reverse := int64(0)

	for x != 0 {
		val := x % 10
		reverse = reverse*10 + int64(val)
		x = x / 10
	}

	if reverse > MaxInt || reverse < MinInt {
		return 0
	}

	return int(int32(reverse))
}

func main() {
	println(reverse(1534236469))
}
