#include "ModuleManager.h"

void ModuleManager::io(IO * iio) {
	iIO = iio;
}

void ModuleManager::pushCore(ModuleInterface * instance) {
	iModules["CORE"]["CORE"] = new ModuleLoader<ModuleInterface,void,void>;
	((ModuleLoader<ModuleInterface,void,void> *)iModules["CORE"]["CORE"])
		->fromCore(instance,iIO,&iModules);
}
