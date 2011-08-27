#ifndef DANBOORU_CPP_GRABBER_MODULE_INTERFACE
#define DANBOORU_CPP_GRABBER_MODULE_INTERFACE

#include "Module.h"

class ModuleInterface : public Module {
	public:
		virtual void interact() = 0;
};

typedef ModuleInterface * interface_create_t();
typedef void interface_destroy_t(ModuleInterface *);

#endif
