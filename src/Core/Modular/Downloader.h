#ifndef DANBOORU_CPP_GRABBER_MODULE_DOWNLOADER
#define DANBOORU_CPP_GRABBER_MODULE_DOWNLOADER

#include "Generic.h"

class ModuleDownloader : public ModuleGeneric {
	public:
		ModuleDownloader() {
		}
		~ModuleDownloader() {
		}
	public:
		void load(std::string const& filepath);
};

#endif
