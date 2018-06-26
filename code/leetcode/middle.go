package main

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	idx1 := len(nums1) / 2
	idx2 := len(nums2) / 2
	if idx1 < idx2 {
		nums1, nums2 = nums2, nums1
		idx1, idx2 = idx2, idx1
	}

	var leftIndex = -1
	var rightIndex = len(nums2)
	for {
		if nums1[idx1] > nums2[idx2] {
			step = (rightIndex - idx2) / 2
			if step == 0 {
				break
			} else {
				leftIndex = idx2
				idx2 += step
				idx1 -= step
			}
		} else {
			step = (idx2 - leftIndex) / 2
			if step == 0 {
				break
			} else {
				rightIndex = idx2
				idx2 -= step
				idx1 += step
			}
		}
	}

	if (len(nums1)+len(nums2))%2 == 0 {

	}

	leftIndex < idx1 < rightIndex
}
