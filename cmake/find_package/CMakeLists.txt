PROJECT(find)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(Threads)

add_executable(main ${CMAKE_THREAD_LIBS_INIT} main.c)
