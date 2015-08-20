#! /bin/bash

echo "give me a num >"
read num
case $num in 
	1)
		echo "num is 1"
		;;
	2)
		echo "num is 2"
		;;
	*)
		echo "num is other"
        ;;
esac
