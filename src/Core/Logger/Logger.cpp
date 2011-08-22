#include "Logger.h"

void Logger::setProgname(std::string const& name) {
	progname = name;
}
void Logger::andBitmask(int b) {
	bitmask &= b;
}
void Logger::orBitmask(int b) {
	bitmask |= b;
}
void Logger::message(std::string const& text) const {
	if (bitmask & LS_MESSAGE) {
		std::cout << text;
	}
}
void Logger::notice(std::string const& text) const {
	if (bitmask & LS_NOTICE) {
		std::cerr << "[Notice] " << text;
	}
}
void Logger::warning(std::string const& text) const {
	if (bitmask & LS_WARNING) {
		std::cerr << "[Warning] " << text;
	}
}
void Logger::error(std::string const& text) const {
	if (bitmask & LS_ERROR) {
		std::cerr << "[Error] " << text;
	}
}
void Logger::debug(std::string const& text) const {
	if (bitmask & LS_DEBUG) {
		std::cout << "[Debug] " << text;
	}
}

