package anonymous

type C struct {
	X float32
	int
	string
}

func MakeInstance() *C {
	return &C{1.0, 10, "ydx"}
}
