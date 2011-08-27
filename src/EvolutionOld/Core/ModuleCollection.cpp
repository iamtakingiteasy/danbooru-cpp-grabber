#include "Grabber.h"

Grabber::ModuleCollection::ModuleCollection(Grabber & c) :
	core(c)
{}

void Grabber::ModuleCollection::scandir(std::string const& path, int depth) {
	if (depth <= 0) return;
	DIR *dip = NULL;
	struct dirent *dit = NULL;
	dip = opendir(path.c_str());
	if (dip == NULL) {
		core.log.debug(0,"Can't open directory");
		closedir(dip);
		return;
	}
	while ((dit = readdir(dip)) != NULL) {
		std::string dname = dit->d_name;
		if (dname == "." || dname == "..") continue;
		struct stat tp;
		std::string fp = path + "/" + dname;
		stat(fp.c_str(),&tp);

		if (S_ISDIR(tp.st_mode)) {
			scandir(fp,--depth);
			continue;
		}

		if (!S_ISREG(tp.st_mode)) continue;

		Modular candidate;

		std::string moduleType;
		std::string moduleName;
		try {
			candidate.load(fp);
			moduleType = *(std::string *)candidate.sym("moduleType");
			moduleName = *(std::string *)candidate.sym("moduleName");
			candidate.unload();
		} catch (std::exception const& e) {
			core.log.debug(1,"Failed to load module " + fp);
			core.log.debug(1,e.what());
		}

		if (moduleType == "downloader") {
			if (loadersDownloader[moduleName].isLoaded()) {
				core.log.debug(0,"Module "
							   + fp
							   + " has already taken name "
							   + moduleName);
				continue;
			}
			try {
				loadersDownloader[moduleName].loadDownloader(fp);
				loadersIndexDownloader.push_back(moduleName);
				core.log.debug(0,"Loaded module " + fp);
				std::vector<Option>::iterator oit;
				std::vector<Option> options = \
					loadersDownloader[moduleName].getInstance()->getOptions();
				for (oit = options.begin(); oit != options.end(); oit++) {
					core.interact.push_option(*oit);
				}
				
			} catch (std::exception const& e) {
				loadersDownloader.erase(moduleName);
				core.log.debug(0,"Failed toload module " + fp);
				core.log.debug(0,e.what());
				continue;
			}
		} else if (moduleType == "board") {
		} else if (moduleType == "handler") {
		}

	}
}

void Grabber::ModuleCollection::loadModules() {
	std::vector<std::string>::const_iterator it;
	for (it = core.conf.moduleDirs.begin(); it != core.conf.moduleDirs.end(); it++) {
		core.log.debug(0,"Entering modules directory " + *it);
		scandir(*it,core.conf.moduleSearchRecursionDepth);
	}
}
