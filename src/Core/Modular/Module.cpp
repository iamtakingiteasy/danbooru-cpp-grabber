#include "Module.h"

Module::Module() {
	handle = NULL;
	wasLoaded = false;
}

Module::~Module() {
	if (wasLoaded) {

#ifdef HAVE_UNIX_MODULAR
		dlclose(handle);
#endif
#ifdef HAVE_WIN_MODULAR
		FreeLibrary((HINSTANCE__*)handle);
#endif
		handle = NULL;
	}
}

void Module::load(std::string const& filepath) {
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
		throw ModuleException(path,"could not load");
	}
	
	wasLoaded = true;
}

void * Module::sym(std::string const& symname) {
	if (!wasLoaded) {
		throw ModuleException(path,"was not loaded");
	}
	void *ptr = NULL;
	
#ifdef HAVE_UNIX_MODULAR
	ptr = dlsym(handle,symname.c_str());
#endif
#ifdef HAVE_WIN_MODULAR
	ptr = (void *)(intptr_t)GetProcAddress((HINSTANCE__*)handle,symname.c_str());
#endif
	
	if (!ptr) {
		throw ModuleException(path,"could not load symbol " + symname);
	}
	return ptr;
}
