bin_PROGRAMS = danbooru-cpp-grabber

danbooru_cpp_grabber_SOURCES = Main.cpp Modular/Generic.cpp Modular/Downloader.cpp


if MINGW
danbooru_cpp_grabber_SOURCES += Modular/ModuleWin.cpp
else
danbooru_cpp_grabber_SOURCES += Modular/ModuleUnix.cpp
endif



#if MINGW
#	danbooru_cpp_grabber_SOURCES += Modular/ModuleWin.cpp
#else
#	danbooru_cpp_grabber_SOURCES += Modular/ModuleUnix.cpp
#endif