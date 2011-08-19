#ifndef DANBOORU_CPP_GRABBER_GENERIC_URLENCODER
#define DANBOORU_CPP_GRABBER_GENERIC_URLENCODER

#include <string>
#include <sstream>
#include <map>

class URLEncoder {
	private:
		std::string result;
	private:
		std::string encode(std::string const& what) {
			std::ostringstream os;
			os << what;
			return os.str();	
		}
	public:
		URLEncoder(std::string const& text) {
			result = encode(text);
		}
		URLEncoder(std::string const& base, std::map<std::string,std::string> const& params) {
			std::map<std::string,std::string>::const_iterator it;
			result = base;
			bool first = true;
			for (it = params.begin(); it != params.end(); it++) {
				if (first) {
					result += "?";
				} else {
					result += "&";
				}
				result += encode(it->first);
				result += "=";
				result += encode(it->second);
			}
		}
		
	public:
		std::string str() {
			return result;
		}
};

#endif
