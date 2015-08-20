CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_FILE(WHICH which /usr/bin)

FIND_LIBRARY(C_LIB X11 /usr/lib /usr/local/lib)
FIND_LIBRARY(C_LIB2 txc_dxtn /usr/lib /usr/local/lib)
FIND_LIBRARY(C_LIB3 util /usr/lib /usr/local/lib)

FIND_PATH(which_path which /usr/bin)

FIND_PROGRAM(which_exe which /usr/bin)

MESSAGE(${WHICH})

MESSAGE(${C_LIB})
MESSAGE(${C_LIB2})
MESSAGE(${C_LIB3})

MESSAGE(${which_path})

MESSAGE(${which_exe})

#next is chapter 9
