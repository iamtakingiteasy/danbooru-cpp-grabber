#ifndef DCPPG_CORE_MODULE_LOADER_H
#define DCPPG_CORE_MODULE_LOADER_H

#include "config.h"

#include <dcppg/Data/ModuleInfo.h>
#include <dcppg/CoreInteract/CoreInteract.h>

#include "ModuleSymer.h"
#include "Logger.h"

#include <string>

template <class I, class C, class D>
class ModuleLoader : public CoreModule {
	private:
		bool         iCore;
		ModuleSymer  iHandle;
		ModuleInfo   iInfo;
		Logger       iLog;
		CoreInteract iCoreInteract;
			

		I * iInstance;
		C * iCreate;
		D * iDestroy;
	private:
		ModuleLoader & operator=(ModuleLoader const& r) {
			return *this;
		}
		ModuleLoader(ModuleLoader const& r) {
		}
	public:
		ModuleLoader() {
			iCore = false;
			iInstance = NULL;
			iCreate   = NULL;
			iDestroy  = NULL;
		}
	public:
		ModuleInfo const& getInfo() const {
			return iInfo;
		}
		Hash<std::string> const& getConf() const {
			return iCoreInteract.iCfg;
		}
		void fromCore(I * instance,
					  IO const* io,
					  modulemapmap const* modmap) {
			iInstance = instance;
			iCreate   = NULL;
			iDestroy  = NULL;

			iInfo = iInstance->getInfo();
			iInfo.type = "CORE";

			iLog.io(io);
			iLog.facility("CORE");

			iCoreInteract.pLog = &iLog;
			iCoreInteract.pMod = modmap;

			iInstance->setCore(&iCoreInteract);
			iInstance->init();
			iInstance->runmod();
		}
		void reload() {
		}
		void load() {
		}
		void unload() {
			iInstance->deinit();
		}
};

#endif
