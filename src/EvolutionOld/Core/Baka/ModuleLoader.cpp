#include "ModuleLoader.h"
#include <stdio.h>



ModuleLoader::ModuleLoader() {
	handle = NULL;
	wasLoaded = false;
}

ModuleLoader::~ModuleLoader() {
	unload();
}

void ModuleLoader::unload() {
	if (wasLoaded) {
		#ifdef HAVE_UNIX_MODULAR
		dlclose(handle);
		#endif
		#ifdef HAVE_WIN_MODULAR
		FreeLibrary((HINSTANCE__*)handle);
		#endif
		handle = NULL;
		wasLoaded = false;
	}
}

bool ModuleLoader::isLoaded() const {
	return wasLoaded;
}

void ModuleLoader::load(std::string const& filepath) {
	if (wasLoaded) {
		throw ModuleException(path,"already loaded");
	}
	path = filepath;

	#ifdef HAVE_UNIX_MODULAR
	handle = dlopen(path.c_str(),RTLD_LAZY);
	#endif
	#ifdef HAVE_WIN_MODULAR
	handle = LoadLibrary(path.c_str());

	#endif

	if (!handle) {
        #ifdef HAVE_UNIX_MODULAR
//		log.debug(dlerror());
        #endif
		throw ModuleException(path,"could not load");
	} else {
        #ifdef HAVE_UNIX_MODULAR
		dlerror();
		#endif
	}

	wasLoaded = true;
}

void * ModuleLoader::sym(std::string const& symname) {
	if (!wasLoaded) {
		throw ModuleException(path,"was not loaded");
	}
	void *ptr = NULL;
	char const* errorMessage = NULL;

	#ifdef HAVE_UNIX_MODULAR
	ptr = dlsym(handle,symname.c_str());
	errorMessage = dlerror();
	#endif
	#ifdef HAVE_WIN_MODULAR
	ptr = (void *)(intptr_t)GetProcAddress((HINSTANCE__*)handle,symname.c_str());
	#endif

	if (!ptr || errorMessage) {
        #ifdef HAVE_UNIX_MODULAR
///		log.debug(errorMessage);
        #endif
		throw ModuleException(path,"could not load symbol " + symname);
	}
	return ptr;
}
