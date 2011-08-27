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
		bool downloaderWithNameExists(std::string const& name) const;
		bool boardWithNameExists(std::string const& name) const;
		bool handlerWithNameExists(std::string const& name) const;

		ModuleDownloader const& lookupDownloader(std::string const& name) const;
		
		std::vector<ModuleDownloader> const& getDownloaders() const;
//		std::vector<ModuleDownloader> const& getBoards() const;
//		std::vector<ModuleDownloader> const& getHandlers() const;
};

#endif
