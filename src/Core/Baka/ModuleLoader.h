#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_LOADER
#define DANBOORU_CPP_GRABBER_CORE_MODULE_LOADER

#include <iostream>
#include <stdexcept>
#include <string>
#include "config.h"

#ifdef HAVE_UNIX_MODULAR
#  include <dlfcn.h>
#endif

#ifdef HAVE_WIN_MODULAR
#  include <windows.h>
#endif

class ModuleException : public std::logic_error {
	public:
		explicit ModuleException(
			std::string const& path,
			std::string const& what_arg) :
			std::logic_error("Module " + path + ": " + what_arg)
		{}
};

class ModuleLoader {
	private:
		void *handle;
	protected:
		bool wasLoaded;
		std::string path;
	public:
		ModuleLoader();
		~ModuleLoader();
	public:
		bool isLoaded() const;
		void load(std::string const& filepath);
		void unload();
		void * sym(std::string const& symname);
};


#endif
