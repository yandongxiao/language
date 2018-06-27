package main

import (
	"fmt"
	"math"
)

func IntFromFloat64(val float64) int {
	if val >= math.MinInt32 && val <= math.MaxInt32 {
		whole, fraction := math.Modf(val)
		if fraction > 0.5 {
			whole++
		}
		return int(whole)
	}
	panic(fmt.Sprintf("overflow"))
}

func main() {
	println(IntFromFloat64(22222222222222222222222222222.9))
}
