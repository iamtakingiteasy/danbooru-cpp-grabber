option(BUILD_INTERFACE_CLI "Build Command-Line user Interface" ON)
if (BUILD_INTERFACE_CLI)
    set(HAVE_INTERFACES TRUE)
    message(STATUS
        "***       building: CLI"
    )
    add_library(interface-cli MODULE
        ${MODULES_INTERFACES_DIR}/CLI/CLI.cpp
    )

else()
    message(STATUS
        "***       skipping: CLI"
    )
endif(BUILD_INTERFACE_CLI)
