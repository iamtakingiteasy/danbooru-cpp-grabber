#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_MODULE_INTERFACE_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_MODULE_INTERFACE_H

#include <dcppg/Data/ModuleInfo.h>

class CoreInteractorModuleLoader {
	public:
		ModuleInfo info;
		void reload();
	public:
};

#endif
