package main

import (
	"fmt"
	"math"
)

const s = "helloworld"

func main() {
	fmt.Println(s)

	// 常量可以是任意精度
	const n = 50000000
	const d = 3e20 / n
	fmt.Println(d)

	// 常量是没有类型的
	fmt.Println(int64(d))
	fmt.Println(math.Sin(d))

}
