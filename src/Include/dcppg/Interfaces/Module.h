#ifndef DCPPG_INTERFACE_MODULE_H
#define DCPPG_INTERFACE_MODULE_H

#include <dcppg/CoreInteract/CoreInteract.h>
#include <dcppg/Data/ModuleInfo.h>

#include <vector>

class ModuleInterface {
	protected:
		CoreInteract * pCore;
	public:
		ModuleInterface() {
			pCore = NULL;
		}
		virtual ~ModuleInterface() {}
	public:
		void setCore(CoreInteract * c) {
			if (pCore == NULL && c != NULL) pCore = c;
		}
		virtual void init() = 0;
		virtual ModuleInfo getInfo() = 0;
		virtual void runmod() = 0;
		virtual void deinit() = 0;

};

#endif
