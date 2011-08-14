#include "Module.h"

#include <windows.h>

Module::Module() {
	handle = NULL;
	wasLoaded = false;
}

Module::~Module() {
	if (wasLoaded) {
		FreeLibrary((HINSTANCE__*)handle);
		handle = NULL;
	}
}

void Module::load(std::string const& filepath) {
	if (wasLoaded) {
		throw ModuleException(path,"already loaded");
	}
	path = filepath;
	handle = LoadLibrary(path.c_str());

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
	ptr = (void *)(intptr_t)GetProcAddress((HINSTANCE__*)handle,symname.c_str());
	if (!ptr) {
		throw ModuleException(path,"could not load symbol " + symname);
	}
	return ptr;
}
