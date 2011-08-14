#include "Curl.h"

CurlDownloader::CurlDownloader(std::string const& url, std::ostream & os) :
	DownloaderInterface(url,os)
{
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeData);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&os);
	}
}

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


void CurlDownloader::perform() {
	if (curl) {
		curl_easy_perform(curl);
	}
}
