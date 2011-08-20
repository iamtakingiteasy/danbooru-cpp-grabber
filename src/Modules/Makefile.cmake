message(STATUS
    "*** Modules:"
)
set(MODULES_DOWNLOADERS_DIR ${MODULES_DIR}/Downloaders)
set(MODULES_BOARDS_DIR ${MODULES_DIR}/Boards)

include(${MODULES_DOWNLOADERS_DIR}/Makefile.cmake)
include(${MODULES_BOARDS_DIR}/Makefile.cmake)
