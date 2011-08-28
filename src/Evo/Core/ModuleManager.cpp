#include "ModuleManager.h"

void ModuleManager::scandir(std::string const& dirpath, int depth) {
	if (depth <= 0) return;
	DIR *dip = NULL;
	struct dirent *dit = NULL;
	dip = opendir(dirpath.c_str());

	if (dip == NULL) {
		log->debug(0,"Can't open directory");
		closedir(dip);
		return;
	}
	while ((dit = readdir(dip)) != NULL) {
		std::string dname = dit->d_name;
		if (dname == "." || dname == "..") continue;
		struct stat tp;
		std::string fp = dirpath + "/" + dname;
		stat(fp.c_str(),&tp);

		if (S_ISDIR(tp.st_mode)) {
			scandir(fp,--depth);
			continue;
		}

		if (!S_ISREG(tp.st_mode)) continue;

		Modular candidate;

		std::string moduleName;
		std::string moduleType;

		try {
			candidate.load(fp);
			moduleType = *(std::string *)candidate.sym("moduleType");
			moduleName = *(std::string *)candidate.sym("moduleName");
			candidate.unload();
		} catch (std::exception const& e) {
			log->debug(1,"Failed to load module " + fp);
			log->debug(1,e.what());
			continue;
		}

		if (moduleType == "interface") {
			if (interfaces[moduleName].isLoaded()) {
				log->debug(0,"Module "
						   + fp
						   + " has already taken name "
						   + moduleName);
				continue;
			}
			try {
				interfaces[moduleName].load(fp);
				interfacesIndex.push_back(moduleName);
				log->debug(0,"Loaded module" + fp);
				std::vector<Option>::iterator oit;
				std::vector<Option> options = interfaces[moduleName].getInstance()->getOptions();
				for (oit = options.begin(); oit != options.end(); oit++) {
					oit->facility = moduleName;
					oit->type = OT_INTERFACE;
					opt->push(*oit);
				}
			} catch (std::exception const& e) {
				interfaces.erase(moduleName);
				interfacesIndex.pop_back();
				log->debug(0,"Failed to load module " + fp);
				log->debug(0,e.what());
			}
		}
		
	}
}
void ModuleManager::load() {
	std::vector<std::string>::const_iterator it;
	for (it = conf->modulePaths.begin(); it != conf->modulePaths.end(); it++) {
		log->debug(0,"Entering modules directory " + *it);
		scandir(*it,conf->moduleRecursionDepth);
	}

}
