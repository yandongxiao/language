package main

import "fmt"

func main() {
	fmt.Printf(Season(3))
}

/* better than if */
func Season(month int) string {
	// switch 和 case 后面跟着的变量必须是相同类型
	// case 后面跟着的可以是变量
	switch month {
	case 12, 1, 2:
		return "Winter"
	case 3, 4, 5:
		return "Spring"
	case 6, 7, 8:
		return "Summer"
	case 9, 10, 11:
		return "Autumn"
	}
	return "Season unknown"
}
