//测试word_letter_counter.go

//test cases:
//  1. Test1: 输入为空
//  2. Test2: 输入一个字符
//  3. Test3: 输入一行字符，没有空白字符
//  4. Test4: 输入一行字符，有空白字符，空格，制表符，还有'\r'字符
//  5. Test5: 输入两行字符，第二行为空
//  6. Test6: 输入两行字符，第二行内容也包含有空白字符，空格，制表符，还有'\r'字符
//  7. Test7: 输入一行字符，只有空白字符

package main

import (
	"testing"
)

func Test1EmptyString(t *testing.T) {
	line, word, char, err := parse("")
	if line != 0 || word != 0 || char != 0 || err != nil {
		t.Errorf("<expect 0,0,0,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test2OneCharacher(t *testing.T) {
	line, word, char, err := parse("A")
	if line != 1 || word != 1 || char != 1 || err != nil {
		t.Errorf("<expect 1,1,1,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test3OneLineWithoutSpace(t *testing.T) {
	line, word, char, err := parse("helloworld")
	if line != 1 || word != 1 || char != 10 || err != nil {
		t.Errorf("<expect 1,1,10,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test4OneLineWithSpace(t *testing.T) {
	line, word, char, err := parse("hello world\tchina\r")
	if line != 1 || word != 3 || char != 15 || err != nil {
		t.Errorf("<expect 1,3,15,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test5EmptySecondLine(t *testing.T) {
	line, word, char, err := parse("hello  world\tchina\r\n")
	if line != 2 || word != 3 || char != 15 || err != nil {
		t.Errorf("<expect 2,3,15,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test6MultiLine(t *testing.T) {
	line, word, char, err := parse("hello  world\tchina\r\nfifty\nnicey")
	if line != 3 || word != 5 || char != 25 || err != nil {
		t.Errorf("<expect 1,3,15,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test7SpaceCharachterLine(t *testing.T) {
	line, word, char, err := parse("\r\t ")
	if line != 1 || word != 0 || char != 0 || err != nil {
		t.Errorf("<expect 1,3,15,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test8(t *testing.T) {
	line, word, char, err := parse("\n\n\n")
	if line != 4 || word != 0 || char != 0 || err != nil {
		t.Errorf("<expect 3,0,0,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}

func Test9(t *testing.T) {
	line, word, char, err := parse("   \t \t \t\t")
	if line != 1 || word != 0 || char != 0 || err != nil {
		t.Errorf("<expect 1,0,0,nil>, got <%d,%d,%d,%v>", line, word, char, err)
	}
}
