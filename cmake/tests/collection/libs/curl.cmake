include(CheckLibraryExists)
check_library_exists(curl curl_easy_init "" HAVE_CURL)
if (HAVE_CURL)
    set(LIBS_CURL
        curl
    )
    if(WIN32)
        set(LIBS_CURL ${LIBS_CURL}
            ws2_32
        )
        add_definitions(-DCURL_STATICLIB)
    endif(WIN32)
endif(HAVE_CURL)
