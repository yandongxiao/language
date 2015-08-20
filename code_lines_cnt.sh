#! /bin/bash

#count the code lines in a project.
code_cnt()
{
	for x in `ls $1`
	do
		f="$1/$x"
		if [ -d $f ]; then
			code_cnt $f
		else
			if [ $(basename "$f") == "CMakeLists.txt" -o "${f##*.}" == "c" -o "${f##*.}" == "h" ]; then     #only count the .c .h and CMakeLists.txt files.
				echo "$f"
				lines=$[ $lines + $(cat "$f" | wc -l | cut -d " " -f 1) ]
			fi
		fi
	done
}

lines=0
code_cnt $1
echo $lines
