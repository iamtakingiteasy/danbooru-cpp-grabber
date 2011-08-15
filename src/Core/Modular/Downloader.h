#ifndef DANBOORU_CPP_GRABBER_MODULE_DOWNLOADER
#define DANBOORU_CPP_GRABBER_MODULE_DOWNLOADER

#include "Generic.h"
#include <danbooru-cpp-grabber/DownloaderInterface.h>

class ModuleDownloader : public ModuleGeneric {
	private:
		downloader_create_t * createPtr;
		downloader_destroy_t * destroyPtr;
	public:
		ModuleDownloader() {
			createPtr = NULL;
			destroyPtr = NULL;
		}
		~ModuleDownloader() {
		}
	public:
		void load(std::string const& filepath);
		DownloaderInterface * create();
		void destroy(DownloaderInterface * instance);
};

#endif
