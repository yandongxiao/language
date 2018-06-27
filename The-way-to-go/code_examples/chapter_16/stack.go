/*
	Passing a value as a parameter in a function or as receiver to a method MAY seem a misuse of memory, because a value is always copied. But on the other hand values are allocated on the stack, which is quick and relatively cheap.
    If you would pass a pointer to the value instead the Go compiler in most cases will see this as the making of an object, and will move this object to the heap,
    so also causing an additional memory allocation: therefore nothing was gained in using a pointer instead of the value!
	!! That is to say: It you value is on stack, just pass it as value !!
*/
