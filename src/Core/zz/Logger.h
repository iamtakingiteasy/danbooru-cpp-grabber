#ifndef DANBOORU_CPP_GRABBER_CORE_LOGGER
#define DANBOORU_CPP_GRABBER_CORE_LOGGER

#include "Config.h"

class Logger {
	private:
		Config & conf;
	public:
		Logger(Config & c) :
			conf(c)
		{}
};

#endif
