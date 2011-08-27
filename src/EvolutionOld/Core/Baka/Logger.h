#ifndef DANBOORU_CPP_GRABBER_CORE_LOGGER
#define DANBOORU_CPP_GRABBER_CORE_LOGGER

#include "Core.h"

#include <iostream>
#include <string>

extern Core core;

class Logger {
	public:
		void multilog(int bits, std::string const& text) const;
		void message(std::string const& text) const;
		void messagePart(std::string const& text) const;
		void notice(std::string const& text) const;
		void warning(std::string const& text) const;
		void error(std::string const& text) const;
		void debug(std::string const& text) const;

};


#endif
