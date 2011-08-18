#ifndef DANBOORU_CPP_GRABBER_DOWNLOADER_CURL
#define DANBOORU_CPP_GRABBER_DOWNLOADER_CURL

#include <danbooru-cpp-grabber/DownloaderInterface.h>
#include <curl/curl.h>

class CurlDownloader : public DownloaderInterface {
	private:
		CURL *curl;
		CURLcode res;
	private:
		size_t static writeData(void *buffer, size_t size, size_t nmemb, void *userp);
	public:
		CurlDownloader() : DownloaderInterface() {}
		~CurlDownloader();
	public:
		void actualPrepare();
		void actualFetch();
};

#endif
