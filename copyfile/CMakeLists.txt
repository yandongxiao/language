cmake_minimum_required(VERSION 2.8)

#copy a file
file(COPY ./CMakeLists.txt DESTINATION "/tmp")
file(COPY ./CMakeLists.txt DESTINATION "/tmp/test")	#can rename CMakeLists.txt to test. however create a test dir.

file(COPY ./build/ DESTINATION "/tmp/abc")

file(COPY ./build DESTINATION "/tmp/abc")	#different with the up.
