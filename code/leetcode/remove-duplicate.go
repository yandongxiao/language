package main

func removeDuplicates(nums []int) int {
	var newIdx = -1
	for i := 0; i < len(nums); i++ {
		elmt := nums[i]
		if i == 0 || nums[newIdx] != elmt {
			newIdx++
			nums[newIdx] = elmt
		}
	}
	return newIdx + 1
}

func main() {
	println(removeDuplicates([]int{1, 2, 3, 3, 4, 5, 5, 6, 6, 6}))
}
