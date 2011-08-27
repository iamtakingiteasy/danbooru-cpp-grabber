#ifndef DANBOORU_CPP_GRABBER_MODULE
#define DANBOORU_CPP_GRABBER_MODULE

#include <vector>
#include <danbooru-cpp-grabber/Generic/OptParser.h>

class ModuleInterface {
	public:
		virtual std::vector<Option> getOptions() = 0;
	public:
		ModuleInterface() {}
		virtual ~ModuleInterface() {}
};

#endif
