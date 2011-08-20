#include "Modular/Downloader.h"
#include <iostream>
#include <map>

int main(int argc, char** argv) {
	try {
		ModuleDownloader test;
		test.load("libdownloader-curl.dll");
//		DownloaderInterface * inter = test.create();
//		inter->prepare("baka",&std::cout);
	} catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
