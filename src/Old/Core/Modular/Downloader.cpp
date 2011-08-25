#include "Downloader.h"

void ModuleDownloader::load(std::string const& filepath) {
	loadBasic(filepath);
	try {
		createPtr = (downloader_create_t *)(intptr_t)moduleHandle.sym("create");
		destroyPtr = (downloader_destroy_t *)(intptr_t)moduleHandle.sym("destroy");
	} catch (ModuleException const& e) {
		std::cerr << e.what() << std::endl;
		throw e;
	}
}

DownloaderInterface * ModuleDownloader::create() const {
	return createPtr();
}

void ModuleDownloader::destroy(DownloaderInterface * instance) const {
	destroyPtr(instance);
}
