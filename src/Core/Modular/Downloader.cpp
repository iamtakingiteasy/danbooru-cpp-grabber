#include "Downloader.h"

void ModuleDownloader::load(std::string const& filepath) {
	loadBasic(filepath);
	try {
//		createPtr = (downloader_create_t *)(intptr_t)moduleHandle.sym("create");
//		destroyPtr = (downloader_destroy_t *)(intptr_t)moduleHandle.sym("destroy");
	} catch (ModuleException const& e) {
		std::cerr << e.what() << std::endl;
	}
}

DownloaderInterface * ModuleDownloader::create() {
	return createPtr();
}

void ModuleDownloader::destroy(DownloaderInterface * instance) {
	destroyPtr(instance);
}
