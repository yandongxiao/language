package main

// 不允许有方法名的重载
func test(a int)    {}
func test(a, b int) {} // previous declaration at ./26.go:4
