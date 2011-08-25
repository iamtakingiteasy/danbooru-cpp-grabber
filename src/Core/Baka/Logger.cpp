#include "Logger.h"

void Logger::multilog(int bits, std::string const& text) const {
	if (bits & LS_WARNING) {
		warning(text);
	}
	if (bits & LS_MESSAGE) {
		message(text);
	}
	if (bits & LS_NOTICE) {
		notice(text);
	}
	if (bits & LS_ERROR) {
		error(text);
	}
	if (bits & LS_DEBUG) {
		debug(text);
	}
}

void Logger::message(std::string const& text) const {
	if (core.loggerFlags & LS_MESSAGE) {
		std::cout << text << std::endl;
	}
}
void Logger::messagePart(std::string const& text) const {
	if (core.loggerFlags & LS_MESSAGE) {
		std::cout << text;
	}
}

void Logger::notice(std::string const& text) const {
	if (core.loggerFlags & LS_NOTICE) {
		std::cerr << "[Notice] " << text << std::endl;
	}
}
void Logger::warning(std::string const& text) const {
	if (core.loggerFlags & LS_WARNING) {
		std::cerr << "[Warning] " << text << std::endl;
	}
}
void Logger::error(std::string const& text) const {
	if (core.loggerFlags & LS_ERROR) {
		std::cerr << "[Error] " << text << std::endl;
	}
}
void Logger::debug(std::string const& text) const {
	if (core.loggerFlags & LS_DEBUG) {
		std::cout << "[Debug] " << text << std::endl;
	}
}
