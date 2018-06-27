package odd

import (
	"testing"
)

func TestIsOdd(t *testing.T) {
	if IsOdd(9) {
		t.Log("9 is odd")
	}
}
