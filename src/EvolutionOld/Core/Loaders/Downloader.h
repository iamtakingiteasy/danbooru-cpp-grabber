#ifndef DANBOORU_CPP_GRABBER_CORE_LOADER_DOWNLOADER
#define DANBOORU_CPP_GRABBER_CORE_LOADER_DOWNLOADER

#include <string>
#include "Generic.h"

#include <danbooru-cpp-grabber/DownloaderInterface.h>

class DownloaderLoader : public GenericLoader {
	private:
		downloader_create_t  * createPtr;
		downloader_destroy_t * destroyPtr;
		DownloaderInterface  * instance;
	public:
		DownloaderLoader();
		~DownloaderLoader();
	public:
		DownloaderInterface * getInstance();
		void loadDownloader(std::string const& filepath);
		DownloaderInterface * create() const;
		void destroy(DownloaderInterface * inst) const;
};

#endif
