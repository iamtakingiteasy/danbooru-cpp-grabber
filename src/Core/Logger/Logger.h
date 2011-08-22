#ifndef DANBOORU_CPP_GRABBER_LOGGER
#define DANBOORU_CPP_GRABBER_LOGGER

#include <iostream>
#include <string>

enum LoggerState {
	LS_MESSAGE = 1<<0,
	LS_NOTICE  = 1<<1,
	LS_WARNING = 1<<2,
	LS_ERROR   = 1<<3,
	LS_DEBUG   = 1<<4
};

class Logger {
	private:
		std::string progname;
		int bitmask;
	public:
		Logger() {
//			bitmask = LS_MESSAGE | LS_NOTICE | LS_WARNING | LS_ERROR;
		}
	public:
		void setProgname(std::string const& name);
		void andBitmask(int b);
		void orBitmask(int b);
	public:
		void message(std::string const& text) const;
		void notice(std::string const& text) const;
		void warning(std::string const& text) const;
		void error(std::string const& text) const;
		void debug(std::string const& text) const;

};


#endif
