#include "Downloader.h"

void ModuleDownloader::load(std::string const& filepath) {
	loadBasic(filepath);
	try {
	} catch (ModuleException const& e) {
		std::cerr << e.what() << std::endl;
	}
}
