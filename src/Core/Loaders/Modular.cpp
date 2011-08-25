#include "Modular.h"

Modular::Modular() {
	handle = NULL;
	wasLoaded = false;
}

Modular::~Modular() {
	unload();
}

void Modular::load(std::string const& filepath) {
	if (wasLoaded) {
		throw ModularException(path,"already loaded");
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
		throw ModularException(path,dlerror());
		#else
		throw ModularException(path,"could not load");
		#endif
	} else {
		#ifdef HAVE_UNIX_MODULAR
		dlerror();
		#endif
	}

	wasLoaded = true;
}


void Modular::unload() {
	if (!wasLoaded) {
		throw ModularException(path,"already loaded");
	}
	#ifdef HAVE_UNIX_MODULAR
	dlclose(handle);
	#endif
	#ifdef HAVE_WIN_MODULAR
	FreeLibrary((HINSTANCE__*)handle);
	#endif
	handle = NULL;
	wasLoaded = false;
}


void * Modular::sym(std::string const& symname) {
	if (!wasLoaded) {
		throw ModularException(path,"was not loaded");
	}
	void *ptr = NULL;
	#ifdef HAVE_UNIX_MODULAR
	char const* errorMessage = NULL;
	ptr = dlsym(handle,symname.c_str());
	errorMessage = dlerror();
	#endif
	#ifdef HAVE_WIN_MODULAR
	ptr = (void *)(intptr_t)GetProcAddress((HINSTANCE__*)handle,symname.c_str());
	#endif

	#ifdef HAVE_UNIX_MODULAR
	if (!ptr || errorMessage) {
	#endif
	#ifdef HAVE_WIN_MODULAR
	if (!ptr) {
	#endif
        #ifdef HAVE_UNIX_MODULAR
		throw ModularException(path,errorMessage);
		#else
		throw ModularException(path,"could not load symbol " + symname);		
        #endif
	}
	return ptr;
}

bool Modular::isLoaded() const {
	return wasLoaded;
}
