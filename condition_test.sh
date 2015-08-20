# /bin/bash -xv

if [ -e /etc/profile ]; then		#use -e instead of -a
	echo "file exist"
fi

if [ -g ./test_if.sh ]; then
	echo "set-group-id is set"
fi

id
touch /home/dxyan/bbbb
if [ -G ./test_if.sh ]; then
	echo "-G set-group-id is set"
fi

if [ -N ./aaa ]; then
	echo "modified moment."
fi

if [ /tmp -ef /tmp ]; then
	echo "same file."
fi

if [ ./aaa -ef ./bbb ]; then
	echo "same file."
fi

if [ ./aaa -nt ./bbb ]; then
	echo "aaa is new than bbb"
fi

nospace=data
if [ -v nospace ]; then
	echo " var nospace is set"
fi

pp=nospace
if [ -R pp ]; then
	echo " var nospace is set and the vaue is a refrentce."
fi

if [ -p ./aaa ]; then
	echo "aaa is a pipe file"
fi

if [ -h /etc/resolv.conf ]; then
	echo "file is a symbolic link"
fi

if [ -L /etc/resolv.conf ]; then
	echo "file is a symbolic link"
fi

if [ -k /tmp ]; then
	echo "/tmp is a sticky file."
fi


if [ -b /dev/sda1 ]; then
	echo "file exist and is a block file"
fi

if [ -f /etc/profile ]; then
	echo "file exist and is a regular file"
fi

if [ -x ./test_if.sh ]; then
	echo "file exist and is executable"
fi



if [ "0"$empty = "0" ]; then
	echo "empty var do not exist"
fi
date
