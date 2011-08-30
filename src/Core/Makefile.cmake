set(core-sources
    ${CORE_DIR}/Main.cpp
    ${CORE_DIR}/Core.cpp
	${CORE_DIR}/IO.cpp
	${CORE_DIR}/Logger.cpp
	${CORE_DIR}/ModuleManager.cpp
	${CORE_DIR}/ModuleLoader.cpp
	${CORE_DIR}/ModuleSymer.cpp		
	${CORE_DIR}/OptionParser.cpp
)

if(HAVE_DLOPEN)
    set(core-libs ${core-libs}
        ${LIBS_DLOPEN}
    )
endif(HAVE_DLOPEN)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
