#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_SPECIFIC_DOWNLOADER
#define DANBOORU_CPP_GRABBER_CORE_MODULE_SPECIFIC_DOWNLOADER

#include "ModuleGeneric.h"
#include <danbooru-cpp-grabber/DownloaderInterface.h>

class ModuleSpecificDownloader : public ModuleGeneric {
	private:
		downloader_create_t * createPtr;
		downloader_destroy_t * destroyPtr;
	public:
		ModuleSpecificDownloader();
		~ModuleSpecificDownloader() {}
	public:
		void load(std::string const& filepath);
		DownloaderInterface * create() const;
		void destroy(DownloaderInterface * instance) const;
};



#endif
