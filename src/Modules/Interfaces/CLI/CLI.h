#ifndef DCPPG_MODULE_INTERFACE_CLI_H
#define DCPPG_MODULE_INTERFACE_CLI_H

#include <dcppg/Interfaces/ModuleInteface.h>

class CLIInterface : public ModuleInterfaceInterface {
	public:
		void init();
		std::vector<Option> getOptions();
		void execte(int argc, char ** argv);
		void deinit();
};

#endif
