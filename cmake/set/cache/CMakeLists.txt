cmake_minimum_required(VERSION 2.8)

#myval will be written to CmakeCache, "10" is a comment
SET (myval "myval" CACHE STRING "COMMENT" FORCE)    # sub directory can see it
SET (myval2 "myval2" CACHE BOOL "COMMENT")    # sub directory can see it

#hide the cache value
#SET (myval "----")

MESSAGE (STATUS ${myval})
MESSAGE (STATUS ${CMAKE_C_COMPILER})

ADD_SUBDIRECTORY(subdir)
