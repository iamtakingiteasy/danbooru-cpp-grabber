#ifndef DCCPG_INTERFACE_CORE_INTERACTOR_H
#define DCCPG_INTERFACE_CORE_INTERACTOR_H

class CoreInteractor {
	public:
		CoreInteractorLogger * log;
	public:
		CoreInteractor(CoreInteractorLogger * l) :
			log(l)
		{}
};

#endif
