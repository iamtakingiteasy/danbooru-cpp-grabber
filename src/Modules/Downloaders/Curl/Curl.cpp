#include "Curl.h"

extern "C" std::string const moduleName = "CurlDownloader";
extern "C" std::string const moduleDescription = "Curl-backended downloader";
extern "C" std::string const moduleVersion = "1.0";
extern "C" std::string const moduleAuthor = "Alexander <itakingiteasy> Tumin";

extern "C" CurlDownloader * create() { return new CurlDownloader; }
extern "C" void destroy(CurlDownloader *ptr) { delete ptr; }


CurlDownloader::~CurlDownloader() {
	if (curl) {
		curl_easy_cleanup(curl);
	}
}

size_t CurlDownloader::writeData(void *buffer, size_t size, size_t nmemb, void *userp) {
	size_t count = size * nmemb;
	std::ostream * dest = (std::ostream *)userp;
	dest->write((char *)buffer,count);
	return count;
}

void CurlDownloader::actualPrepare() {
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeData);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,os);
	}
}

void CurlDownloader::actualFetch() {
	if (curl) {
		curl_easy_perform(curl);
	}
}
