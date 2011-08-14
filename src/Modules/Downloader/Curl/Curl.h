#ifndef DANBOORU_CPP_GRABBER_DOWNLOADER_CURL
#define DANBOORU_CPP_GRABBER_DOWNLOADER_CURL

#include <danbooru-cpp-grabber/DownloaderInterface.h>

#include <curl/curl.h>

class CurlDownloader : DownloaderInterface {
	private:
		CURL *curl;
		CURLcode res;
	private:
		size_t static writeData(void *buffer, size_t size, size_t nmemb, void *userp);
	public:
		CurlDownloader(std::string const& url, std::ostream & os);
		~CurlDownloader();
	public:
		void perform();
};

#endif
