set(core-sources
    ${CORE_DIR}/Main.cpp
    ${CORE_DIR}/Grabber.cpp
    ${CORE_DIR}/Logger.cpp
    ${CORE_DIR}/CLIInteractor.cpp
    ${CORE_DIR}/Loaders/Modular.cpp
    ${CORE_DIR}/Loaders/Generic.cpp
    ${CORE_DIR}/Loaders/Downloader.cpp
    ${CORE_DIR}/ModuleCollection.cpp
)

if(HAVE_DLOPEN)
    set(core-libs ${core-libs}
        ${LIBS_DLOPEN}
    )
endif(HAVE_DLOPEN)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
