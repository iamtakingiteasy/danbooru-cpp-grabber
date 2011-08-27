#ifndef DANBOORU_CPP_GRABBER_MODULE_INTERFACE_CLI
#define DANBOORU_CPP_GRABBER_MODULE_INTERFACE_CLI

#include <danbooru-cpp-grabber/Module/ModuleInterface.h>
#include <danbooru-cpp-grabber/Generic/Option.h>

class CLIInterface : ModuleInterface {
	private:
		static void hListAll(std::string const& arg, void * usr);
	public:
		void init(Hash * o, Logger * l);
		std::vector<Option> getOptions();
		void interact();
		void deinit();
		
};

#endif
