#include "Generic.h"

void ModuleGeneric::loadBasic(std::string const& filepath) {
	try {
		moduleHandle.load(filepath);
		name = *(std::string *)moduleHandle.sym("moduleName");
		description = *(std::string *)moduleHandle.sym("moduleDescription");
		version = *(std::string *)moduleHandle.sym("moduleVersion");
		author = *(std::string *)moduleHandle.sym("moduleAuthor");
	} catch (ModuleException const& e) {
		std::cerr << e.what() << std::endl;
	}
}
