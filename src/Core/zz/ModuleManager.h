#ifndef DANBOORU_CPP_GRABBER_CORE_MODULEMANAGER
#define DANBOORU_CPP_GRABBER_CORE_MODULEMANAGER

#include "Config.h"
#include "Logger.h"

class ModuleManager {
	private:
		Config & conf;
		Logger & log;
	public:
		ModuleManager(Config & c, Logger & l) :
			conf(c), log(l)
		{}
};

#endif
