set(core-sources
    ${CORE_DIR}/Main.cpp
    ${CORE_DIR}/Logger/Logger.cpp
    ${CORE_DIR}/Modular/Module.cpp
    ${CORE_DIR}/Modular/Generic.cpp
    ${CORE_DIR}/Modular/Downloader.cpp
    ${CORE_DIR}/Modular/Manager.cpp
)

if(HAVE_DLOPEN)
    set(core-libs ${core-libs}
        ${LIBS_DLOPEN}
    )
endif(HAVE_DLOPEN)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
