package main

import "fmt"

type flt func(int) bool

type slice_split func([]int) ([]int, []int)

func isOdd(num int) bool {
	if num%2 == 0 {
		return false
	}

	return true
}

func filter(f flt) slice_split {
	return func(nums []int) (yes, no []int) {
		for e := range nums {
			if f(e) {
				yes = append(yes, e)
			} else {
				no = append(yes, e)
			}
		}
		return
	}
}

func main() {
	split := filter(isOdd)
	nums := []int{1, 2, 3, 4}
	s1, s2 := split(nums)

	fmt.Println(s1)
	fmt.Println(s2)
}
