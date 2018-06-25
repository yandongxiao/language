package main

import "fmt"

func main() {
	nums := []int{1, 2, 3, 4, 15}
	rels := filter(nums, isOdd)
	fmt.Println("Odd number is %v", rels)
}

func isOdd(num int) bool {
	if num%2 == 0 {
		return false
	}
	return true
}

func filter(nums []int, f func(int) bool) []int {
	var resl []int
	for _, e := range nums {
		if f(e) {
			resl = append(resl, e)
		}
	}

	return resl
}
