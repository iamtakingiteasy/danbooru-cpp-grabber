set(core-sources
    ${CORE_DIR}/Main.cpp
)

if (HAVE_DLOPEN)
    set(core-sources ${core-sources}
        ${CORE_DIR}/Modular/ModuleUnix.cpp
    )
    set(core-libs
        ${LIBS_DLOPEN}
    )
elseif(HAVE_LOADLIBRARY)
    set(core-sources ${core-sources}
        ${CORE_DIR}/Modular/ModuleWin.cpp
    )
else()
    message(SEND_ERROR
        "No dlopen()-like functionality found in your system. Aborting."
    )
endif (HAVE_DLOPEN)

set(core-sources ${core-sources}
    ${CORE_DIR}/Modular/Generic.cpp
    ${CORE_DIR}/Modular/Downloader.cpp
)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
