#include "ModuleManager.h"

void ModuleManager::scandir(std::string const& path, int depth) {
	if (depth <= 0) return;
	DIR * dip = NULL;
	struct dirent *dit = NULL;
	struct stat tp;
	dip = opendir(path.c_str());
	if (dip == NULL) {
		log.debug("Can't open directory");
		closedir(dip);
		return;
	}
	while ((dit = readdir(dip)) != NULL) {
		if (!strcmp(dit->d_name,".") || !strcmp(dit->d_name,"..")) continue;
		std::string fp = std::string(path + "/" + dit->d_name);
		stat(fp.c_str(),&tp);
		if (S_ISDIR(tp.st_mode)) {
			scandir(fp,--depth);
			continue;
		}
		if(!S_ISREG(tp.st_mode)) continue;
		ModuleLoader candidate;
				
		std::string moduleType;
		std::string moduleName;
		try {
			candidate.load(fp);
		} catch (std::exception const& e) {
			candidate.unload();
			continue;
		}

		try {
			moduleType = *(std::string *)candidate.sym("moduleType");
			moduleName = *(std::string *)candidate.sym("moduleName");
		} catch (std::exception const& e) {
 			log.debug("Failed to get meta-info of module " + fp);
			continue;
		}

		
		if (false) {
		} else if (moduleType == "downloader") {
			if (core.downloaders[moduleName].isLoaded()) {
				log.debug("Module " + fp + " has already token name " + moduleName);
				continue;
			}
			try {
				core.downloaders[moduleName].load(fp);
				core.downloadersIndex.push_back(moduleName);
				log.debug("Loaded module " + fp);
			} catch (std::exception const& e) {
				core.downloaders.erase(moduleName);
				log.debug("Failed to load module " + fp);
				continue;
			}
		} else if (moduleType == "board") {
		} else if (moduleType == "handler") {
		}

	}
	closedir(dip);
	
}

void ModuleManager::loadModules() {
	std::vector<std::string>::const_iterator it;
	for (it = core.modulePaths.begin(); it != core.modulePaths.end(); it++) {
		log.debug("Entering modules directory " + *it);
		scandir(*it,core.moduleRecursionDepth);
	}
}
