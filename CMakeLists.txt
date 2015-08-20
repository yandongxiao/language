project(test)

SET(CMAKE_DEBUG_POSTFIX "d")
#SET(LIBRARY_OUTPUT_PATH /home/ubuntu14/share/temp/xxx/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY /home/ubuntu14/share/temp/xxx/lib)
add_library(main main.c)

add_executable(main2.exe main2.c)
SET_TARGET_PROPERTIES( main2.exe
     PROPERTIES
     DEBUG_OUTPUT_NAME main2
     RELEASE_OUTPUT_NAME "main2"
)

get_filename_component(PA .. ABSOLUTE)
MESSAGE(STATUS ${PA})

MESSAGE(STATUS "C ${CMAKE_C_FLAGS}")
