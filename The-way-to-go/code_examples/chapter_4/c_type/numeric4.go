package main

import (
	"fmt"
	"math"
)

func Unit8FromInt(val int) (uint8, error) {
	if val >= 0 && val <= math.MaxUint8 {
		return uint8(val), nil
	}
	return 0, fmt.Errorf("out of range integer")
}

func main() {
	val1, _ := Unit8FromInt(100)
	println(val1)

	_, err := Unit8FromInt(1000)
	fmt.Println(err)
}
