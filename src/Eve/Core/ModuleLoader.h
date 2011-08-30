#ifndef DCPPG_CORE_MODULE_LOADER_H
#define DCPPG_CORE_MODULE_LOADER_H

#include <dcppg/Data/ModuleInfo.h>
#include <dcppg/Data/Option.h>
#include <dcppg/Interfaces/CoreInteractor.h>

#include "Modular.h"
#include "CoreLogger.h"

#include <vector>
#include <string>

template <class I, class C, class D>
class ModuleLoader {
	private:
		std::string type;
		std::string path;
		Modular handle;
		ModuleInfo info;
		std::vector<Option> options;

		CoreInteractor icore;
		CoreLogger ilog;
		

		I * instance;
		C * create;
		D * destroy;
	private:
		ModuleLoader(ModuleLoader const& r) {
		}
		ModuleLoader & operator=(ModuleLoader const& r) {
			return *this;
		}
		void loadParts() {
			handle.load(path);
			create  = (C*)(intptr_t)handle.sym("create");
			destroy = (D*)(intptr_t)handle.sym("destroy");
			
			instance = create();
			info     = instance->getInfo();
			options  = instance->getOptions();
			
		}
	public:
		ModuleLoader() {
			instance = NULL;
			create   = NULL;
			destroy  = NULL;
		}
		~ModuleLoader() {
			unload();
		}
	public:
		void load(std::string const& p, std::string const& t, Logger const* l) {
			if (instance) return;
			if (path.empty() && !p.empty()) path = p;
			
			if(l == NULL) return;
			
			loadParts();
			type = t;
	
			ilog.setRealLogger(l);
			ilog.setFacility(type + "/" + info.name);
			
			icore.setLogger(&ilog);
			
			instance->setCore(&icore);
			
		}
		void reload() {
			unload();
			if (path.empty()) return;
			
			loadParts();
			ilog.setFacility(type + "/" + info.name);
			
			instance->setCore(&icore);
			
		}
		void unload() {
			if (!instance && !destroy && !create) return;
			if (instance && destroy) destroy(instance);
			handle.unload();
			instance = NULL;
			create   = NULL;
			destroy  = NULL;
		}
};

#endif
