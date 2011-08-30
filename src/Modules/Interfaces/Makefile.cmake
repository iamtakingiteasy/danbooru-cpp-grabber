message(STATUS
    "***    Interfaces:"
)

include(${MODULES_INTERFACES_DIR}/CLI/Makefile.cmake)

if (NOT HAVE_INTERFACES)
    message(SEND_ERROR
        "No interface modules can be built. Aborting."
    )
endif(NOT HAVE_INTERFACES)