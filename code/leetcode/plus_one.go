package main

import "fmt"

func plusOne2(digits []int) []int {
	val := 0
	for _, x := range digits {
		val = val*10 + x
	}
	val++

	result := make([]int, len(digits)+1)
	idx := len(result) - 1
	for val != 0 {
		x := val % 10
		result[idx] = x
		idx--
		val = val / 10
	}

	idx++
	return result[idx:]
}

func plusOne(digits []int) []int {
	next := 1
	result := make([]int, len(digits)+1)
	for i := len(digits) - 1; i >= 0; i-- {
		x := digits[i]
		if x+next == 10 {
			next = 1
			result[i+1] = 0
		} else {
			result[i+1] = x + next
			next = 0
		}
	}
	if next == 1 {
		result[0] = 1
		return result
	}
	return result[1:]
}

func main() {
	fmt.Println(plusOne([]int{1, 2, 3}))
}
