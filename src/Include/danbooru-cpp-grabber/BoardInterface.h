#ifndef DANBOORU_CPP_GRABBER_BOARD_INTERFACE
#define DANBOORU_CPP_GRABBER_BOARD_INTERFACE

#include <string>
#include <vector>

class BoardInterface {
	protected:
		std::string boardURL;
	public:
		BoardInterface() {}
		virtual ~BoardInterface() {}
	public:
		void setBoardURL(std::string const& url) {
			boardURL = url;
		}
		virtual std::string genURLQueryTags(std::string const& tagPattern) = 0;
		virtual std::string genURLQueryPosts(std::vector<std::string> const& tags) = 0;
};

#endif
