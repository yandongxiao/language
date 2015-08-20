#! /bin/bash

str='   abfdas  fdsfsaf d  *  \t'

echo "$str" | sed 's/^[ \t]*\(.*\)[ \t]*/\1/g' -
echo '$str' | sed 's/^[ \t]*\(.*\)[ \t]*/\1/g' -
echo $str | sed 's/^[ \t]*\(.*\)[ \t]*/\1/g' -

abc=`echo "$str" | sed 's/^[ \t]*\(.*\)[ \t]*/\1/g' -`
echo "$abc"
