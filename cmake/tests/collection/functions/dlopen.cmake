include(CheckLibraryExists)
check_library_exists(dl dlopen "" HAVE_DLOPEN)
if (HAVE_DLOPEN)
    set(LIBS_DLOPEN
        dl
    )
endif(HAVE_DLOPEN)