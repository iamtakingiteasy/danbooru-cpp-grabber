#include "ModuleManager.h"

void ModuleManager::io(IO * iio) {
	iIO = iio;
}

modulemapmap * ModuleManager::getModules() {
	return &iModules;
}

void ModuleManager::pushCore(ModuleInterface * instance,CoreOption * opt) {
	iModules["CORE"]["CORE"] = new ModuleLoader<ModuleInterface,void,void>;
	((ModuleLoader<ModuleInterface,void,void> *)iModules["CORE"]["CORE"])
		->fromCore(instance,iIO,&iModules,opt);
	log =
		&((ModuleLoader<ModuleInterface,void,void> *)
		 iModules["CORE"]["CORE"])->getLogger();
}

void ModuleManager::scanDir(std::string const& path, int depth) {
	if (depth <= 0) return;

	DIR *dip = NULL;
	struct dirent *dit = NULL;
	dip = opendir(path.c_str());
	
	if (dip == NULL) {
		log->debug(0,"Can't open directory");
		closedir(dip);
		return;
	}
	while ((dit = readdir(dip)) != NULL) {
		std::string dname = dit->d_name;
		if (dname == "." || dname == "..") continue;
		struct stat tp;
		std::string fp = path + "/" + dname;
		stat(fp.c_str(),&tp);

		if(S_ISDIR(tp.st_mode)) {
			scanDir(fp,--depth);
			continue;
		}

		if (!S_ISREG(tp.st_mode)) continue;

		ModuleSymer candidate;

		std::string moduleType;
		std::string moduleName;

		try {
			candidate.load(fp);
			moduleType = *(std::string *)candidate.sym("moduleType");
			moduleName = *(std::string *)candidate.sym("moduleName");
			candidate.unload();
		} catch (std::exception const &e) {
			log->debug(1,"Failed to load module " + fp);
			log->debug(1,e.what());
			continue;
		}

		
	}
	closedir(dip);
	
}

void ModuleManager::loadModules() {
	Hash<std::string> const& coreConf =
		((ModuleLoader<ModuleInterface,void,void> *)
		 iModules["CORE"]["CORE"])->getConf();

	int depth = coreConf["module"]["depth"];
	Hash<std::string>::vector_const_iterator it;
	for (it = coreConf["module"]["paths"].beginVector();
		 it != coreConf["module"]["paths"].endVector();
		 it++) {
		log->debug(0,"Opening directory " + (std::string)*it);
		scanDir((std::string)*it,depth);
		
	}
	
}
