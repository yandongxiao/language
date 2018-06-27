package main

import "fmt"

func Max(nums ...int) (max int, err error) {
	fmt.Printf("type=%T\n", nums)
	if len(nums) == 0 {
		return -1, fmt.Errorf("%s", "empty array")
	}

	max = nums[0]
	for _, e := range nums {
		if max < e {
			max = e
		}
	}
	return
}

func main() {
	fmt.Println(Max())
	fmt.Println(Max(1, 2, 3, 4, 5))
}
