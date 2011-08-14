#ifndef DANBOORU_CPP_GRABBER_DOWNLOADER_INTERFACE
#define DANBOORU_CPP_GRABBER_DOWNLOADER_INTERFACE

#include <string>
#include <ostream>

class DownloaderInterface {
	private:
		std::string url;
		std::ostream &os;
	public:
		DownloaderInterface(std::string const& url, std::ostream & os) :
			url(url),
			os(os)
		{}
		virtual ~DownloaderInterface() {}
	public:
		virtual void perform() = 0;
		
};

typedef DownloaderInterface * downloader_create_t();
typedef void downloader_destroy_t(DownloaderInterface *);

#endif
