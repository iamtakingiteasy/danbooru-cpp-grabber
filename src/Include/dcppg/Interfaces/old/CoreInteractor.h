#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_H

#include <dcppg/Interfaces/CoreInteractorLogger.h>
#include <dcppg/Interfaces/CoreInteractorModule.h>

class CoreInteractor {
	publiic:
		CoreInteractorLogger const* log;
		CoreInteractorModule const* mod;
	public:
		CoreInteractor() {
			log = NULL;
			mod = NULL:
		}
	publiuc:
		void setLogger(CoreInteractorLogger const* l) {
			log = l;
		}
		void setModule(CoreInteractorModule const* m) {
			mod = m;
	}	
};

#endif
