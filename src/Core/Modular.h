#ifndef DANBOORU_CPP_GRABBER_CORE_MODULAR
#define DANBOORU_CPP_GRABBER_CORE_MODULAR

#include <stdexcept>
#include <string>
#include "cmake_config.h"

#ifdef HAVE_UNIX_MODULAR
#  include <dlfcn.h>
#endif

#ifdef HAVE_WIN_MODULAR
#  include <windows.h>
#endif

class Modular {
	private:
		void *handle;
	protected:
		bool wasLoaded;
		std::string path;
	public:
		Modular();
		~Modular();
	public:
		bool isLoaded() const;
		void load(std::string const& filepath);
		void unload();
		void * sym(std::string const& symname);
};


#endif
