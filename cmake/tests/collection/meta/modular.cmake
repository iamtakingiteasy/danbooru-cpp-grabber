set(HAVE_UNIX_MODULAR FALSE)
set(HAVE_WIN_MODULAR FALSE)

if(HAVE_DLOPEN)
    set(HAVE_UNIX_MODULAR TRUE)
elseif(HAVE_LOADLIBRARY)
    set(HAVE_WIN_MODULAR TRUE)
else()
    message(SEND_ERROR
        "Have no modular support in your system. Aborting."
    )
endif(HAVE_DLOPEN)