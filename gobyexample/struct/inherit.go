package main

type Parent struct {
	name string
}

func (p Parent) getName() string {
	return p.name
}

type Child struct {
	Parent
}

func main() {
	c := new(Child)
	c.name = "jack"      // 不但可以直接访问匿名类的field
	println(c.getName()) // 还可以直接访问匿名类的方法
}
