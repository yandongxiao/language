package main

func searchInsert(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}

	begin := 0
	end := len(nums)
	idx := (end - begin) / 2
	for nums[idx] != target {
		println(nums[idx])
		if nums[idx] > target {
			newIdx := begin + (idx-begin)/2
			if newIdx == idx {
				return idx
			}
			end = idx
			idx = newIdx
		} else if nums[idx] < target {
			newIdx := idx + (end-idx)/2
			if idx == newIdx {
				return idx + 1
			}
			begin = idx
			idx = newIdx
		}
	}
	return idx
}

func main() {
	println(searchInsert([]int{1, 3, 5, 6}, 0))
}
