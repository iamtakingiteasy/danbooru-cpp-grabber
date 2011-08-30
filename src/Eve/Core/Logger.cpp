#include "Logger.h"

Logger::Logger() {
	flags = 0 | VL_MESSAGE | VL_NOTICE | VL_WARN | VL_ERROR;
	debugLevel = 0;
	showGroups = true;
	showFacilities = false;
}
void Logger::orFlags(VerboseLevel f) {
	flags |= f;
}

void Logger::incrDebugLevel() {
	debugLevel++;
}

void Logger::toggleShowFacilities() {
	showFacilities ^= 1;
}

void Logger::toggleShowGroups() {
	showGroups ^= 1;
}

void Logger::message(std::string const& facility, std::string const& text) const {
	if (flags & VL_MESSAGE) {
		std::cout << text << std::endl;
	}
}
void Logger::notice (std::string const& facility, std::string const& text) const {
	if (flags & VL_NOTICE) {
		if (showGroups) std::cout << "[Notice] ";
		std::cout << text << std::endl;
	}
}
void Logger::warn   (std::string const& facility, std::string const& text) const {
	if (flags & VL_WARN) {
		if (showGroups) std::cout << "[Warn] ";
		std::cout << text << std::endl;
	}
}
void Logger::error  (std::string const& facility, std::string const& text) const {
	if (flags & VL_ERROR) {
		if (showGroups) std::cout << "[Error] ";
		std::cout << text << std::endl;
	}
}
void Logger::debug  (
	std::string const& facility,
	int level,
	std::string const& text) const {
	if (flags & VL_DEBUG) {
		if (level <= debugLevel) {
			if (showGroups) std::cout << "[Debug" << level << "] ";
			std::cout << text << std::endl;
		}
	}
}
