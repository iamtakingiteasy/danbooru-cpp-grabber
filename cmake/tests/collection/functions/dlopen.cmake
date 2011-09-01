include(CheckLibraryExists)

check_library_exists(dl dlopen "" HAVE_DL_DLOPEN)
check_library_exists(c dlopen "" HAVE_C_DLOPEN)

if (HAVE_DL_DLOPEN)
   set(HAVE_DLOPEN TRUE)
    set(LIBS_DLOPEN
        dl
    )
endif(HAVE_DL_DLOPEN)

if (HAVE_C_DLOPEN)
   set(HAVE_DLOPEN TRUE)
    set(LIBS_DLOPEN
        c
    )
endif(HAVE_C_DLOPEN)