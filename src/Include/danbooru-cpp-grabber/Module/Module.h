#ifndef DANBOORU_CPP_GRABBER_MODULE_MODULE
#define DANBOORU_CPP_GRABBER_MODULE_MODULE

#include <vector>

#include <danbooru-cpp-grabber/Generic/Option.h>
#include <danbooru-cpp-grabber/Generic/Logger.h>
#include <danbooru-cpp-grabber/Generic/Hash.h>

class Module {
	public:
		Module() {}
		virtual ~Module() {}
	public:
		virtual void init(Hash * o, Logger * l) = 0;
		virtual std::vector<Option> getOptions()= 0;
		virtual void deinit() = 0;
};

#endif
