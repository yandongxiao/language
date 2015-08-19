#! /bin/bash

CASE1=/tmp/empty
if [ ! -x ${CASE1} ]; then
    mkdir ${CASE1}
fi
./file.type.statistics ${CASE1}

CASE2=/tmp/reg_and_dir
if [ ! -x ${CASE2} ]; then
    mkdir ${CASE2}
fi
touch ${CASE2}/reg_file
mkdir ${CASE2}/dir_file
./file.type.statistics ${CASE2}

#todo
CASE3=/tmp/reg_and_dir/
