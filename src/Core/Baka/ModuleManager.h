#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_MANAGER
#define DANBOORU_CPP_GRABBER_CORE_MODULE_MANAGER

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <string>
#include <vector>

#include "Main.h"

class ModuleManager {
	private:
		void scandir(std::string const& path, int depth);
	public:
		ModuleManager() {}
		~ModuleManager() {}
	public:
		void loadModules();
		
};



#endif
