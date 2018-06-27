package main

func longestCommonPrefix(strs []string) string {
	if len(strs) == 0 {
		return ""
	}

	first := strs[0]
	idx := 0
	for idx = 0; idx < len(first); idx++ {
		ch := first[idx]
		isCommon := true
		for _, str := range strs[1:] {
			if len(str) < idx+1 || str[idx] != ch {
				isCommon = false
				break
			}
		}

		if !isCommon {
			break
		}
	}

	// first[:0] 返回的是空字符串
	return first[:idx]
}

func main() {
	println(longestCommonPrefix([]string{}))
}
