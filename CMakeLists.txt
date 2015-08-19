CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

FILE(MAKE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-D_GNU_SOURCE)

SET (FIFO_TEST fifo_write fifo_read)

SET (SYSTEM_TEST execl_argu argu_print)

SET (SID_PGRP_TEST getsid getsid_test)

SET (SIGNAL_TEST signal_test1 signal_test2 signal_test3
                 signal_test4 signal_test5 signal_test6
                 signal_test6_child)

SET (PTHEAD_TEST pthread_test1 pthread_test2 pthread_test3
                 pthread_test4 pthread_test5 pthread_test6
                 pthread_test8 pthread_test9)

SET (ALL_TESTS ${FIFO_TEST} ${SIGNAL_TEST} ${SYSTEM_TEST}
               ${SID_PGRP_TEST} ${PTHEAD_TEST})

FOREACH(it ${ALL_TESTS})
    ADD_EXECUTABLE(${it} ${it}.c)
    TARGET_LINK_LIBRARIES(${it} pthread)
ENDFOREACH(it)

