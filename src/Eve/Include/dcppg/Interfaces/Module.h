#ifndef DCPPG_INTERFACE_MODULE_H
#define DCPPG_INTERFACE_MODULE_H

#include <dcppg/Interfaces/CoreInteractor.h>
#include <dcppg/Data/Option.h>
#include <dcppg/Data/ModuleInfo.h>

#include <vector>

class ModuleInterface {
	private:
		CoreInteractor * core;
	public:
		ModuleInterface() {
			core = NULL;
		}
		virtual ~ModuleInterface() {}
	public:
		void setCore(CoreInteractor * c) {
			if (core == NULL && c != NULL) core = c;
		}
		virtual void init() = 0;
		virtual std::vector<Option> getOptions() = 0;
		virtual ModuleInfo getInfo() = 0;
		virtual void deinit() = 0;

};

#endif
