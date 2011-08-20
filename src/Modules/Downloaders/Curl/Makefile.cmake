set(module-downloader-curl-sources
    ${MODULES_DOWNLOADERS_DIR}/Curl/Curl.cpp
)

add_library(downloader-curl MODULE
    ${module-downloader-curl-sources}
)

target_link_libraries(downloader-curl 
    ${LIBS_CURL}
)