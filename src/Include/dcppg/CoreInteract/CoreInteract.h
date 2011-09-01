#ifndef DCPPG_CORE_INTERACT_H
#define DCPPG_CORE_INTERACT_H

#include <dcppg/CoreInteract/CoreLogger.h>
#include <dcppg/CoreInteract/CoreModule.h>
#include <dcppg/CoreInteract/CoreOption.h>
#include <dcppg/Data/Hash.h>

class CoreInteract {
	public:
		CoreOption        * pOpt;
		CoreLogger   const* pLog;
		modulemapmap const* pMod;
		Hash<std::string>   iCfg;
		
	public:
		CoreInteract() {
			pLog = NULL;
			pMod = NULL;
		}
};

#endif
