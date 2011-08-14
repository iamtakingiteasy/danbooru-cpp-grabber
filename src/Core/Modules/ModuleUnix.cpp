#include "Module.h"

#include <dlfcn.h>

Module::Module() {
	handle = NULL;
	wasLoaded = false;
}

Module::~Module() {
	if (wasLoaded) {
		dlclose(handle);
		handle = NULL;
	}
}

void Module::load(std::string const& filepath) {
	if (wasLoaded) {
		throw ModuleException(path,"already loaded");
	}
	path = filepath;
	handle = dlopen(path.c_str(),RTLD_LAZY);

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
	ptr = dlsym(handle,symname.c_str());
	if (!ptr) {
		throw ModuleException(path,"could not load symbol " + symname);
	}
	return ptr;
}
