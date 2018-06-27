package main

func myroutine(ch chan int) {
	ch <- 10
	ch <- 11
	ch <- 12
	close(ch)
}

func main() {
	ch := make(chan int)
	/* If one producer close the chann, other routine will be affected */
	go myroutine(ch)

	for val := range ch {
		println(val)
	}

}
