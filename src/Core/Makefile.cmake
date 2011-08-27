set(core-sources
    ${CORE_DIR}/Main.cpp
    ${CORE_DIR}/Application.cpp
    ${CORE_DIR}/OptParser.cpp
    ${CORE_DIR}/Modular.cpp
    ${CORE_DIR}/ModuleLoader.cpp
    ${CORE_DIR}/ModuleManager.cpp
)

if(HAVE_DLOPEN)
    set(core-libs ${core-libs}
        ${LIBS_DLOPEN}
    )
endif(HAVE_DLOPEN)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
