#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_H

#include <dcppg/Interfaces/CoreInteractorLogger.h>
#include <dcppg/Interfaces/CoreInteractorModule.h>

class CoreInteractor {
	public:
		CoreInteractorLogger const* log;
		CoreInteractorModule const* mod;
	public:
		CoreInteractor() {
			log = NULL;
			mod = NULL;
		}
	public:
		void setLogger(CoreInteractorLogger const* l) {
			if (log == NULL && l != NULL) log = l;
		}

};

#endif
