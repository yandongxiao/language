# they are same effect 

SET (VARIABLE "1" CACHE INTERNAL "1")
IF("${VARIABLE}" MATCHES "^${VARIABLE}$")
    MESSAGE (STATUS "variable is defined, but empty")
ENDIF()


IF("${VARIABLE2}" MATCHES "^${VARIABLE2}$")
    MESSAGE (STATUS "variable is not defined")
ENDIF()
