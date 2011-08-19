//#include "Modular/Downloader.h"
#include <danbooru-cpp-grabber/Generic/URLEncoder.h>
#include <iostream>
#include <map>

int main(int argc, char** argv) {
//	ModuleDownloader test;
//	test.load("modules/downloaders/libdownloader-curl.so");
//	DownloaderInterface * inter = test.create();
//	inter->prepare("baka",&std::cout);
	std::map<std::string,std::string> params;
	params["abc"]="efg";
	params["rrr"]="baka shi";
//	params.push_back("fff");
	std::cout << URLEncoder("baka",params).str() << std::endl;
	return 0;
}
