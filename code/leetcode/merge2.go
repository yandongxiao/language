package main

func merge(nums1 []int, m int, nums2 []int, n int) {
	idx1 := m
	idx2 := 0
	nums1[idx1] = nums1[0]
	for i := 0; i < m+n; i++ {
		if nums1[idx1] < nums2[idx2] {
			nums1[i] = nums1[idx1]
			nums1[idx1] = nums1[i+1]
		} else {
			nums1[i] = nums2[idx2]
			nums2[idx2] = nums1[i+1]
		}
	}
	for i := 0; i < m; i++ {

	}
}
