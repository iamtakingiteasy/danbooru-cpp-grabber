message(STATUS
    "*** Modules:"
)
set(MODULES_INTERFACES_DIR ${MODULES_DIR}/Interfaces)
#set(MODULES_DOWNLOADERS_DIR ${MODULES_DIR}/Downloaders)

include(${MODULES_INTERFACES_DIR}/Makefile.cmake)
#include(${MODULES_DOWNLOADERS_DIR}/Makefile.cmake)

