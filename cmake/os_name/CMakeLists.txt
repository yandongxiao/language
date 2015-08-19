SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET (os $ENV{os})

#Method 1
IF (${os} STREQUAL "Linux")
    MESSAGE (STATUS "linux os")
ELSEIF (${os} STREQUAL "Windows")
    MESSAGE (STATUS "windows os")
ENDIF (${os} STREQUAL "Linux")


IF (WIN32)
    MESSAGE (STATUS "windows os")
ELSEIF(UNIX)
    MESSAGE (STATUS "linux os")
ENDIF(WIN32)
