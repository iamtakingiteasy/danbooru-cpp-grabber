#ifndef DANBOORU_CPP_GRABBER_MODULAR_MANAGER
#define DANBOORU_CPP_GRABBER_MODULAR_MANAGER

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "Module.h"
#include "Downloader.h"
#include "Logger/Logger.h"
#include <vector>
#include <string>

class ModuleManager {
	private:
		std::vector<std::string> modulePaths;
		std::vector<ModuleDownloader> downloaderModules;
	private:
		void scandir(std::string const& path);
	public:
		ModuleManager() {}
		~ModuleManager() {}
	public:
		void setPaths(std::vector<std::string> const& paths);
		void loadModules();
	public:
		std::vector<ModuleDownloader> const& getDownloaders();
};

#endif
