#! /bin/bash
#
# when you execute the script, shell do the fllowing things:
#
# shell try to call execlp to run this the executable file (think it is a executable file
# in PATH dir). 
# If failed, execlp will consider it as a script.
# If interpreter declareed, sh fork->exec the interpreter to interpret the script
# If not, shell fork->exec a shell again, and use it to interpret the script.
#
# what kind of shell to use is decided by the parrent shell type.
# my shell is bash shell
#

echo $0
for arg in $*
do
    echo ${arg}
done
