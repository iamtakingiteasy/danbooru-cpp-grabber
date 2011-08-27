#ifndef DANBOORU_CPP_GRABBER_CORE_INTERACTOR_CLI
#define DANBOORU_CPP_GRABBER_CORE_INTERACTOR_CLI

#include "Config.h"
#include "Interactor.h"

class CLIInteractor : Interactor {
	public:
		CLIInteractor(Config & c) :
			Interactor(c)
		{}
};

#endif
