#include "Modular/Downloader.h"

int main(int argc, char** argv) {
	ModuleDownloader test;
	test.load("modules/downloaders/libdownloader-curl.so");
	return 0;
}
