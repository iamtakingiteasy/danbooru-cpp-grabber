#ifndef DCPPG_CORE_MODULE_MANAGER_H
#define DCPPG_CORE_MODULE_MANAGER_H

#include "config.h"

#include <dcppg/Interfaces/Module.h>
#include <dcppg/CoreInteract/CoreModule.h>
#include <dcppg/CoreInteract/CoreOption.h>
#include <dcppg/Data/ModuleInfo.h>

#include "IO.h"
#include "ModuleLoader.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


#include <map>
#include <vector>
#include <string>

class ModuleManager {
	private:
		IO *iIO;
		Logger const* log;
		modulemapmap iModules;
	private:
		void scanDir(std::string const& path, int depth);
	public:
		ModuleManager() {
		}
		~ModuleManager() {
			modulemapmap::iterator outter;
			modulemap::iterator inner;
			for (outter = iModules.begin(); outter != iModules.end(); outter++) {
				for (inner = outter->second.begin();
						 inner != outter->second.end();
					 inner++) {
					inner->second->unload();
					delete inner->second;
				}
			}
		}
	public:
		modulemapmap * getModules();
		void io(IO * iio);
		void pushCore(ModuleInterface * instance, CoreOption * opt);
		void loadModules();
};

#endif
