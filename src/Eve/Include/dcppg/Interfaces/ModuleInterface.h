#ifndef DCPPG_INTERFACE_MODULE_INTERFACE_H
#define DCPPG_INTERFACE_MODULE_INTERFACE_H

#include <dcppg/Interfaces/Module.h>
#include <map>
#include <string>

class ModuleInterfaceInterface : public ModuleInterface {
	public:
		ModuleInterfaceInterface() :
			ModuleInterface()
		{}
		virtual ~ModuleInterfaceInterface() {}
	public:
		virtual void execute(int argc, char ** argv) = 0;
};

typedef ModuleInterfaceInterface * interface_create_t();
typedef void interface_destroy_t(ModuleInterfaceInterface *);

#endif
