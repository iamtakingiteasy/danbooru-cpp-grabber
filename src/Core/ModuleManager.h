#ifndef DCPPG_CORE_MODULE_MANAGER_H
#define DCPPG_CORE_MODULE_MANAGER_H

#include "config.h"

#include <dcppg/Interfaces/Module.h>
#include <dcppg/CoreInteract/CoreModule.h>
#include <dcppg/Data/ModuleInfo.h>

#include "IO.h"
#include "ModuleLoader.h"


#include <map>
#include <vector>
#include <string>

class ModuleManager {
	private:
		IO *iIO;
		modulemapmap iModules;
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
		void io(IO * iio);
		void pushCore(ModuleInterface * instance);
};

#endif
