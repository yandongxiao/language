MESSAGE(STATUS ${CMAKE_FIND_ROOT_PATH})

MESSAGE(STATUS ${CMAKE_PREFIX_PATH})

MESSAGE(STATUS ${CMAKE_LIBRARY_ARCHITECTURE})

MESSAGE(STATUS ${CMAKE_LIBRARY_PATH})

MESSAGE(STATUS ${CMAKE_FRAMEWORK_PATH})


cmake_minimum_required(VERSION 2.8)

function(findfile filename filepalce)
    MESSAGE("filename == ${${filename}}")      #${filename}==filena, ${${filename}} == aaa
    MESSAGE("filename == ${ARGV0}")      #${filename}==filena, ${${filename}} == aaa
    set(${filename} "123" PARENT_SCOPE)        #must use "PARENT_SCOPE", or "123" only used in function.
    set(filename "usr")
endfunction(findfile)

set(filena "aaa")
set(filepalce)
findfile (filena filepalce "wq" "dsadsa")

MESSAGE(STATUS ${filena})       #123
MESSAGE(STATUS ${filepalce})    #""
