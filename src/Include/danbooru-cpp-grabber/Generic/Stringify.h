#ifndef DANBOORU_CPP_GRABBER_GENERIC_STRINGIFY
#define DANBOORU_CPP_GRABBER_GENERIC_STRINGIFY

#include <string>
#include <sstream>

class Stringify {
	private:
		std::ostringstream ss;
	public:
		Stringify() {};
		Stringify(int num) {
			ss << num;
		}
	public:
		std::string str() {
			return ss.str();
		}
};
#endif
