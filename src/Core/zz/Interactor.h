#ifndef DANBOORU_CPP_GRABBER_CORE_INTERACTOR
#define DANBOORU_CPP_GRABBER_CORE_INTERACTOR

#include "Config.h"

class Interactor {
	private:
		Config & conf;
	public:
		Interactor(Config & c) :
			conf(c)
		{}
};

#endif
