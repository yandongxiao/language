package main

func main() {
	// A common idiom used to let the main program block indefinitely while other goroutines run is to place select {} as the last statement in a main function.}
	// 但是如果没有其它协程，会发生deadlock
	select {}
}
