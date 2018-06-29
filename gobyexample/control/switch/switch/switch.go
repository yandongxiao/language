package main

import (
	"fmt"
	"time"
)

func main() {
	i := 2
	fmt.Print("Write ", i, " as ")

	switch i {
	case 1:
		// 不需要指定break，这是golang的默认行为
		fmt.Println("One")
	case 2:
		fmt.Println("Two")
	case 3:
		fmt.Println("Three")
	}

	// You can use commas to separate multiple expressions in the same case statement.
	switch time.Now().Weekday() {
	case time.Saturday, time.Sunday:
		fmt.Println("It's the weekend")
	default:
		fmt.Println("It's a weekday")
	}

	// switch without an expression is an alternate way to express if/else logic.
	switch {
	case time.Hour < 12: // 这时候case表达式返回true or false
		fmt.Println("It's before noon")
	default:
		fmt.Println("It's after noon")
	}

	// type switch
	whatAmI := func(i interface{}) {
		switch t := i.(type) {
		case bool:
			fmt.Println("I am bool")
		default:
			fmt.Printf("I do not konow, %T\n", t)
		}
	}
	whatAmI(true)
	whatAmI(3)
}
