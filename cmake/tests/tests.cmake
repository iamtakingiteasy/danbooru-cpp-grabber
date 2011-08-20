include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/collection/functions/dlopen.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/collection/functions/LoadLibrary.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/collection/libs/curl.cmake)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/include/config.cmake 
    include/config.h)