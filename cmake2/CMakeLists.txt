PROJECT(dudud)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(LIBRARY_OUTPUT_PATH /opt)

ADD_SUBDIRECTORY(src)

#add_executable(xxx $<TARGET_OBJECTS:ttt> main.c)

add_executable(xxx main.c ttt.a)
