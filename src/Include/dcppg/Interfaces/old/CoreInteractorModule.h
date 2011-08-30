#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_MODULE_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_MODULE_H

#include <dcppg/Data/ModuleInfo.h>

#include <vector>

class CoreInteractorModule {
	public:
		std::vector<ModuleInfo<> > getInterfaceModules();
//		std::vector<ModuleInfo> getDownloaderModules();
//		std::vector<ModuleInfo> getParserModules();
//		std::vector<ModuleInfo> getHandlerModules();
};

#endif
