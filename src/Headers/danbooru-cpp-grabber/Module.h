#ifndef DCPPG_MODULE
#define DCPPG_MODULE

#include <string>

class ModuleHandler {
	private:
		void *handle;
		std::string path;
	private:
		void moduleOpen(std::string const& filepath);
		void moduleClose();
	public:
		ModuleHandler(std::string const& filepath) {
			handle = NULL;
			moduleOpen(filepath);
		}
		~ModuleHandler() {
			if (handle) {
				moduleClose();
				handle = NULL;
			}
		}
	public:
		void* moduleSym(std::string const& symname);
};


#endif
