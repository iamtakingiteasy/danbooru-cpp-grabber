#include "Grabber.h"

void Grabber::Logger::multi(int bits, std::string const& text) const {
	if (bits & LT_MESSAGE) {
		message(text);
	}
	if (bits & LT_NOTICE) {
		notice(text);
	}
	if (bits & LT_WARNING) {
		warning(text);
	}
	if (bits & LT_ERROR) {
		error(text);
	}
	if (bits & LT_DEBUG) {
		debug(text);
	}
}

void Grabber::Logger::message(std::string const& text) const {
	if (core.conf.loggerFlags & LT_MESSAGE) {
		std::cout << text << std::endl;
	}
}


void Grabber::Logger::notice(std::string const& text) const {
	if (core.conf.loggerFlags & LT_NOTICE) {
		std::cout << "[Notice] " << text << std::endl;
	}
}


void Grabber::Logger::warning(std::string const& text) const {
	if (core.conf.loggerFlags & LT_WARNING) {
		std::cout << "[Warning] " << text << std::endl;
	}
}
void Grabber::Logger::error(std::string const& text) const {
	if (core.conf.loggerFlags & LT_ERROR) {
		std::cout << "[Error] " << text << std::endl;
	}
}

void Grabber::Logger::debug(std::string const& text) const {
	if (core.conf.loggerFlags & LT_DEBUG) {
		std::cout << "[Debug] " << text << std::endl;
	}
}


