include_directories(
    ${CMAKE_SOURCE_DIR}
)

configure_file(${CMAKE_SOURCE_DIR}/Config/config.h.cmake ${CMAKE_SOURCE_DIR}/config.h)