#ifndef DANBOORU_CPP_GRABBER_MODULE_MANAGER
#define DANBOORU_CPP_GRABBER_MODULE_MANAGER

#include "Downloader.h"

#include <string>
#include <vector>

class ModuleManager {
	private:
		std::vector<std::string> modulePaths;
		std::vector<ModuleDownloader> downloaderModules;
	private:
	public:
		ModuleManager();
		~ModuleManager() {};
	public:
		void setModulePaths(std::vector<std::string> const& paths);
		void loadModules();
		std::vector<ModuleDownloader> const& getDownloaders();
		
		
};

#endif
