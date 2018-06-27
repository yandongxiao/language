package main

import "os"
import ""
func getenv() {
    fmt.println
    os.Getenv("PATH")
}
func main() {
	str := os.Getenv("JAVA_HOME")
	println(str)

	data := make([]byte, 100)
	n, _ := os.Stdin.Read(data)
	println(n, string(data))

}
