message(STATUS
    "***    Downloaders:"
)
if (HAVE_CURL)
    include(${MODULES_DOWNLOADERS_DIR}/Curl/Makefile.cmake)
	set(HAVE_DOWNLOADER TRUE)
    message(STATUS
        "***       Curl ............................... yes"
    ) 
else()
    message(STATUS
        "***       Curl ............................... no"
    ) 
endif(HAVE_CURL)

if (NOT HAVE_DOWNLOADER)
    message(SEND_ERROR
        "No downloader modules can be built. Aborting."
    )
endif(NOT HAVE_DOWNLOADER)