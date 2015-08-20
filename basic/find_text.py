#! /usr/bin/python

from sys import argv
from os import path
import re

# print the match line.
def print_match_line (pattern, files) :
    for fname in files : 
        linenum = 1
        f = open(fname)
        for line in f.readlines():
            lower = line.lower()
            mc = re.search(pattern.lower(), lower)
            if mc : 
                print("%s:%d :%s" % (fname, linenum, line), end="")
            linenum += 1
        f.close() 

# count the number of matched string.
def print_match_string(pattern, files) :
    pattern = pattern.lower()
    cmpl = re.compile(pattern)

    count = 0
    for fname in files :
        f = open(fname)
        linenum = 1
        for line in f.readlines() :
            i = 0
            sc = cmpl.search(line.lower(), i)
            while sc :
                print("%s:%d : %s " % (fname, linenum, line[sc.start() : sc.start()+len(sc.group())] ))
                i = sc.start()+len(sc.group())
                count += 1
                sc = cmpl.search(line.lower(), i)
            linenum += 1
        f.close()
    print ("the matched number of string is : %d", count)


# 1.parse arguments
if len(argv) < 3 :
    print("usage : ./find_text pattern filename.")
    exit()

pattern = argv[1]
i = 2
files = []
while( i < len(argv) ):     # argv[0] is the script name.
    files.append(argv[i])
    i += 1

# 2. make sure the file exist.
parsefiles = []
for x in files:
    if not path.isfile(x) :
        print("%s file dose not exist." % x)
        continue
    parsefiles.append(x)
files = parsefiles;

# operation.

print_match_line(pattern, files)
print_match_string(pattern, files)

print("done.")
