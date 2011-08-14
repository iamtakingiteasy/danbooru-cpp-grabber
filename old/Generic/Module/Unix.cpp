#include <dlfcn.h>
#include <danbooru-cpp-grabber/Module.h>

void Generic::Module::moduleOpen() {
	moduleHandle = dlopen(path.c_str(),RTLD_LAZY);
}

void Generic::Module::moduleClose() {
	dlclose(moduleHandle);
}

void* Generic::Module::moduleSym(std::string const& symname) {
	return dlsym(moduleHandle,symname.c_str());
}



