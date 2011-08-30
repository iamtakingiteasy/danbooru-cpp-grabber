#ifndef DCPPG_CORE_CORE_H
#define DCPPG_CORE_CORE_H

#include <dcppg/Interfaces/ModuleInterface.h>
#include <dcppg/Data/Option.h>

#include "Logger.h"
#include "ModuleManager.h"

#include <string>
#include <vector>
#include <map>

class Core {
	private:
		Logger  log;
		ModuleManager modules;
		std::vector<Option> coreOpt;
	private:
	private:
		void loadModules();
		void coreOptions();
	public:
		void run(int argc, char ** argv);
		
};

#endif
