cmake_minimum_required(VERSION 2.8)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
include (CheckFunctionExistsEx)
CHECK_FUNCTION_EXISTS_EX(gettimeofday EVENT__HAVE_GETTIMEOFDAY)
