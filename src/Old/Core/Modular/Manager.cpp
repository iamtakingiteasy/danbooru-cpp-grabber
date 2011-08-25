#include "Manager.h"

extern Logger log;

void ModuleManager::setPaths(std::vector<std::string> const& paths) {
	modulePaths = paths;
}

bool ModuleManager::downloaderWithNameExists(std::string const& name) const {
	std::vector<ModuleDownloader>::const_iterator it;
	for (it = downloaderModules.begin(); it != downloaderModules.end(); it++) {
		if (it->getName() == name) return true;
	}
	return false;
}

ModuleDownloader const& ModuleManager::lookupDownloader(std::string const& name) const {
	std::vector<ModuleDownloader>::const_iterator it;
	for (it = downloaderModules.begin(); it != downloaderModules.end(); it++) {
		if (it->getName() == name) return *it;
	}
	throw std::runtime_error("No downloader module with name " + name + " found");
}

std::vector<ModuleDownloader> const& ModuleManager::getDownloaders() const {
	return downloaderModules;
}

void ModuleManager::scandir(std::string const& path) {
	DIR * dip = NULL;
	struct dirent *dit = NULL;
	struct stat tp;
	dip = opendir(path.c_str());
	if (dip == NULL) {
		return;
	}
	while ((dit = readdir(dip)) != NULL) {
		if (!strcmp(dit->d_name,".") || !strcmp(dit->d_name,"..")) continue;
		std::string fp = std::string(path + "/" + dit->d_name);
		stat(fp.c_str(),&tp);
		if (S_ISDIR(tp.st_mode)) {
			scandir(fp);
			continue;
		}
		if(!S_ISREG(tp.st_mode)) continue;
		Module candidate;
		std::string moduleType;
		std::string moduleName;
		try {
			candidate.load(fp);
		} catch (std::exception const& e) {
			continue;
		}
		try {
			moduleType = *(std::string *)candidate.sym("moduleType");
			moduleName = *(std::string *)candidate.sym("moduleName");
		} catch (std::exception const& e) {
			log.debug("Failed to get type or name of module " + fp + "\n");
			continue;
		}
		if (downloaderWithNameExists(moduleName)) {
			log.debug("Dup of existing module " + moduleName + "@" + fp +"\n");
			continue;
		}
		if (false) {
		} else if (moduleType == "downloader") {
			try {
				downloaderModules.push_back(ModuleDownloader());
				downloaderModules.back().load(fp);
				log.debug("Loaded module " + fp + "\n");
			} catch (std::exception const& e) {
				log.debug("Failed to load module " + fp + ". Unloading.\n");
				downloaderModules.pop_back();
			}
		} else if (moduleType == "board") {
		} else if (moduleType == "handler") {
		} else {
			log.debug("Unknown type of module " + fp + ".\n");
			continue;
		}

	}
	closedir(dip);
	
}

void ModuleManager::loadModules() {
	std::vector<std::string>::iterator it;
	for (it = modulePaths.begin(); it != modulePaths.end(); it++) {
		log.debug("Entering into modules directory " + *it + "\n");
		scandir(*it);
	}
}
