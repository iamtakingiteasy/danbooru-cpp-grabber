set(module-interface-cli-sources
    ${MODULES_INTERFACES_DIR}/CLI/CLI.cpp
)

add_library(interface-cli MODULE
    ${module-interface-cli-sources}
)