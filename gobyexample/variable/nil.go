package main

type Person struct {
	name string
	age  int
}

func main() {
	var s []int
	var m map[int]int
	var c chan int
	if s != nil || m != nil || c != nil {
		panic("s should be nil")
	} else {
		println("引用类型初始化值为nil")
	}

	persons := make(map[string]Person)
	if persons["jack"].name != "" {
		panic("it is not true")
	} else {
		println("因为struct是值类型，persons返回了一个zero-value")
	}

	// cannot use nil as type Person in assignment
	//persons["jack"] = nil
	//fmt.Println(persons["jack"])
}
