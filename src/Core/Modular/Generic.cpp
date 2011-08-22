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
		throw e;
	}
}

std::string const& ModuleGeneric::getName() const {
	return name;
}
std::string const& ModuleGeneric::getDescription() const {
	return description;
}
std::string const& ModuleGeneric::getVersion() const {
	return version;
}
std::string const& ModuleGeneric::getAuthor() const {
	return author;
}
