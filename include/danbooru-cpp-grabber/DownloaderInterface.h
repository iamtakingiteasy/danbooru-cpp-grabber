#ifndef DANBOORU_CPP_GRABBER_DOWNLOADER_INTERFACE
#define DANBOORU_CPP_GRABBER_DOWNLOADER_INTERFACE

#include <string>
#include <ostream>

class DownloaderInterface {
	protected:
		std::string url;
		std::ostream *os;
		bool wasPrepared;
	private:
		virtual void actualPrepare() = 0;
		virtual void actualFetch() = 0;
	public:
		DownloaderInterface() {
			os = NULL;
			wasPrepared = false;
		}
		virtual ~DownloaderInterface() {}
	public:
		void prepare(std::string const& urlArg, std::ostream *osArg) {
			url = urlArg;
			os = osArg;
			wasPrepared = true;
			actualPrepare();
		};
		void fetch() {
			if (wasPrepared) {
				actualFetch();
			}
		}
};

typedef DownloaderInterface * downloader_create_t();
typedef void downloader_destroy_t(DownloaderInterface *);

#endif
