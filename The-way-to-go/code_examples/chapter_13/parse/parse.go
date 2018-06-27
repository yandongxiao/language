// parse.go
package parse

import (
	"fmt"
	"strconv"
	"strings"
)

// A ParseError indicates an error in converting a word into an integer.
type ParseError struct {
	Index int    // The index into the space-separated list of words.
	Word  string // The word that generated the parse error.
	Err   error  // The raw error that precipitated this error, if any.
}

// String returns a human-readable error message.
func (e *ParseError) String() string {
	return fmt.Sprintf("pkg parse: error parsing %q as int", e.Word)
}

// Parse parses the space-separated words in in put as integers.
func Parse(input string) (numbers []int, err error) {
	defer func() {
		if r := recover(); r != nil { /* the return value of recover is interface{} */
			var ok bool
			err, ok = r.(error)
			if !ok {
				err = fmt.Errorf("pkg: %v", r)
			} else {
				println("----------")
			}
		}
	}()

	fields := strings.Fields(input)
	numbers = fields2numbers(fields)
	return
}

func fields2numbers(fields []string) (numbers []int) {
	if len(fields) == 0 {
		panic("no words to parse")
		// panic(fmt.Errorf("no words to parse"))
	}
	for idx, field := range fields {
		num, err := strconv.Atoi(field)
		if err != nil {
			panic(&ParseError{idx, field, err}) //you can parse a struct pointer
		}
		numbers = append(numbers, num)
	}
	return
}
