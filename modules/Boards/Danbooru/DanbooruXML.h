#ifndef DANBOORU_CPP_GRABBER_BOARD_DANBOORU_XML
#define DANBOORU_CPP_GRABBER_BOARD_DANBOORU_XML

#include <danbooru-cpp-grabber/BoardInterface.h>

class DanbooruXML : public BoardInterface {
	public:
		DanbooruXML() {}
		~DanbooruXML() {}
	public:
		std::string genURLQueryTags(std::string const& tagPattern);
		std::string genURLQueryPosts(std::vector<std::string> const& tags);
};

#endif
