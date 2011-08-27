#include "Generic.h"

void GenericLoader::loadGeneric(std::string const& filepath) {
	moduleHandle.load(filepath);
	name        = *(std::string *)moduleHandle.sym("moduleName");
	description = *(std::string *)moduleHandle.sym("moduleDescription");
	version     = *(std::string *)moduleHandle.sym("moduleVersion");
	author      = *(std::string *)moduleHandle.sym("moduleAuthor");
}

bool GenericLoader::isLoaded() const { return moduleHandle.isLoaded(); }

std::string const& GenericLoader::getName()        const { return name; }
std::string const& GenericLoader::getDescription() const { return description; }
std::string const& GenericLoader::getVersion()     const { return version; }
std::string const& GenericLoader::getAuthor()      const { return author; }
