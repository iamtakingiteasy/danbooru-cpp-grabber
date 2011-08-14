#include <windows.h>
#include <danbooru-cpp-grabber/Module.h>

void Generic::Module::moduleOpen() {
	moduleHandle = LoadLibrary(path.c_str());
}

void Generic::Module::moduleClose() {
	FreeLibrary((HINSTANCE__*)moduleHandle);
}

void* Generic::Module::moduleSym(std::string const& symname) {
	return (void *)(intptr_t)GetProcAddress((HINSTANCE__*)moduleHandle,symname.c_str());
}
