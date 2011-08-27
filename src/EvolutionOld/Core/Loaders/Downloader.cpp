#include "Downloader.h"

DownloaderLoader::DownloaderLoader() {
	createPtr  = NULL;
	destroyPtr = NULL;
	instance   = NULL;
}

DownloaderLoader::~DownloaderLoader() {
	if (instance) {
		destroyPtr(instance);
	}
}

DownloaderInterface * DownloaderLoader::getInstance() {
	return instance;
}

void DownloaderLoader::loadDownloader(std::string const& filepath) {
	loadGeneric(filepath);
	createPtr = (downloader_create_t *)(intptr_t)moduleHandle.sym("create");
	destroyPtr = (downloader_destroy_t *)(intptr_t)moduleHandle.sym("destroy");
	instance = createPtr();
}

DownloaderInterface * DownloaderLoader::create() const {
	return createPtr();
}

void DownloaderLoader::destroy(DownloaderInterface * inst) const {
	destroyPtr(inst);
}
