package main

type MyInter interface {
	test()
}

type Stringer interface {
	String() string
}

type Mystruct struct{}

func (Mystruct) test() {
	println("nihao")
}

func (Mystruct) String() string {
	return "123"
}

func main() {
	data := Mystruct{}
	data.test()
	if sv, ok := data.(Stringer); ok {
		fmt.Printf("------")
	}
	/*
		if sv, ok := data.(MyInter); ok {
			println(sk.test())
		}
	*/
}
