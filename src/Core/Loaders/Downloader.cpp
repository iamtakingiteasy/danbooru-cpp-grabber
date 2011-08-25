#include "Downloader.h"

DownloaderLoader::DownloaderLoader() {
	createPtr  = NULL;
	destroyPtr = NULL;
}

void DownloaderLoader::loadDownloader(std::string const& filepath) {
	loadGeneric(filepath);
	createPtr = (downloader_create_t *)(intptr_t)moduleHandle.sym("create");
	destroyPtr = (downloader_destroy_t *)(intptr_t)moduleHandle.sym("destroy");
}

DownloaderInterface * DownloaderLoader::create() const {
	return createPtr();
}

void DownloaderLoader::destroy(DownloaderInterface * instance) const {
	destroyPtr(instance);
}
