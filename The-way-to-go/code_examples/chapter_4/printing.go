package main

import "fmt"

func main() {
	var nums = []int{1, 2, 3}
	fmt.Printf("%v\n", nums)
	fmt.Println(nums) /* so smart */
	//	fmt.Printf("%d\n", nums) /* OK */

	var nums2 = []string{"niha", "bad"}
	fmt.Printf("%v\n", nums2)
	fmt.Println(nums2) /* so smart */
	//	fmt.Printf("%d\n", nums2) /* not OK */

	println(nums)
}
