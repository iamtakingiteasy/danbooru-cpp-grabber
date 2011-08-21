#include "Modular/Manager.h"
#include <iostream>
#include <vector>
#include <map>

int main(int argc, char** argv) {
	ModuleManager modules;

	std::vector<std::string> modulePaths;

	modulePaths.push_back("./"); // TODO should be removed from non-dev builds
	modulePaths.push_back("~/.config/danbooru-cpp-grabber/modules");
	modulePaths.push_back("/usr/lib/danbooru-cpp-grabber/modules");

	modules.setPaths(modulePaths);

	modules.loadModules();
	
	return 0;
	
}
