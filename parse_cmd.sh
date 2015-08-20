#! /bin/bash

i=1
echo $*
for arg in $*
do
    if [ $i -eq 3 ];then
        mhostname=$3
    fi

    if [ $i -lt 4 ];then
        ((i++))
        continue
    fi

    string=${string}" "${arg}
    ((i++))
done

echo $mhostname
echo $string
