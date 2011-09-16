add_library(dcppg-data STATIC 
#  ${CORE_DIR}/data/varstring.cpp
  ${CORE_DIR}/data/dlinked.cpp
#  ${CORE_DIR}/data/option.cpp
  )

set(core-sources
  ${CORE_DIR}/main.cpp
#  ${CORE_DIR}/core_config.c
  ${CORE_DIR}/grabber.cpp
  ${CORE_DIR}/configuration.cpp
  ${CORE_DIR}/optparser.cpp
  )

set(core-libs ${core-libs}
  dcppg-data
  )

if(HAVE_DLOPEN)
  set(core-libs ${core-libs}
    ${LIBS_DLOPEN}
    )
endif(HAVE_DLOPEN)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
