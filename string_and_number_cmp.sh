#! /bin/bash

#compare with number.
num=10
if [ $num -lt 100 ]; then
	echo "$num is little than 100"
fi

if [ $num -le 10 ]; then
	echo "$num is little or equal 10"
fi

if [ $num -gt 8 ]; then
	echo "$num is greater or equal 8"
fi

if [ $num -ge 10 ]; then
	echo "$num is greater or equal 10"
fi

if [ $num -eq 10 ]; then
	echo "$num is equal to 10"
fi

#compare with string, Note: [ $aa="bb" ] is not right, no matter what value @aa is,
#the condition is alwayse ture.

num="hello"

if [ $num > "hello" ] ; then
	echo "$num is equal to hello"
fi

if [ $num ]; then
	echo "0 is not a number but a string"
fi

if [ $num = 0 ]; then
	echo "string "
fi

