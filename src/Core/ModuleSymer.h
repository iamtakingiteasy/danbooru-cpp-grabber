#ifndef DCPPG_CORE_MODULE_SYMER_H
#define DCPPG_CORE_MODULE_SYMER_H

#include "config.h"

#include <stdexcept>
#include <string>

#ifdef HAVE_UNIX_MODULAR
#  include <dlfcn.h>
#endif

#ifdef HAVE_WIN_MODULAR
#  include <windows.h>
#endif

class ModuleSymer {
	private:
		void *handle;
	protected:
		bool wasLoaded;
		std::string path;
	public:
		ModuleSymer();
		~ModuleSymer();
	public:
		bool isLoaded() const;
		void load(std::string const& filepath);
		void unload();
		void * sym(std::string const& symname);
};



#endif
