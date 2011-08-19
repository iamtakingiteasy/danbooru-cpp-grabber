set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 1)
set(GCC_PREFIX "i686-mingw32")
set(CMAKE_C_COMPILER "${GCC_PREFIX}-gcc")
set(CMAKE_RC_COMPILER "${GCC_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER "${GCC_PREFIX}-g++")
set(CMAKE_RANLIB "${GCC_PREFIX}-ranlib")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-static-libgcc -static-libstdc++")