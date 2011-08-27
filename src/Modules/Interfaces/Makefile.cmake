message(STATUS
    "***    Interfaces:"
)

include(${MODULES_INTERFACES_DIR}/CLI/Makefile.cmake)

set(HAVE_INTERFACES TRUE)

message(STATUS
    "***       CLI ................................ yes"
)

#if (NOT HAVE_INTERFACES)
#    message(SEND_ERROR
#       "No interfaces modules can be built. Aborting."
#    )
#ndif(NOT HAVE_DOWNLOADER)