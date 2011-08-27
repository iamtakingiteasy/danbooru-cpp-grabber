#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_MANAGER
#define DANBOORU_CPP_GRABBER_CORE_MODULE_MANAGER


#include <danbooru-cpp-grabber/Module/ModuleInterface.h>
#include <danbooru-cpp-grabber/Generic/Config.h>
#include <danbooru-cpp-grabber/Generic/Logger.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include "ModuleLoader.h"
#include "OptParser.h"
#include "Modular.h"

#include <string>
#include <map>

class ModuleManager {
	private:
		Config * conf;
		Logger * log;
		OptParser * opt;
		std::map<
		std::string,
		ModuleLoader<
			ModuleInterface,
			interface_create_t,
			interface_destroy_t>
		> interfaces;
		std::vector<std::string> interfacesIndex;

	private:
		void scandir(std::string const& dirpath, int depth);
	public:
		ModuleManager(Config * c, Logger * l, OptParser * o) :
			conf(c),
			log(l),
			opt(o)
		{}
	public:
		void load();
		
};


#endif
