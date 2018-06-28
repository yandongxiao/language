package main

func removeElement(nums []int, val int) int {
	if len(nums) == 0 {
		return 0
	}
	end := len(nums) - 1
	for begin := 0; begin <= end; begin++ {
		elmt := nums[begin]
		if elmt != val {
			continue
		}

		if begin < end {
			nums[begin] = nums[end]
			begin--
			end--
		} else {
			end--
		}
	}
	return end + 1
}

func main() {
	nums := []int{2, 2}
	println(removeElement(nums, 2))
}
