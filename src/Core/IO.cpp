#include "IO.h"

void IO::incrDebugLevel() {
	iDebugLevel++;
}
void IO::showFacility(bool value) {
	iShowFacility = value;
}
void IO::showGroups(bool value) {
	iShowGroups = value;
}

void IO::orFlags(int flags) {
	iFlags |= flags;
}

void IO::message(std::string const& facility, std::string const& text) const {
	if (iFlags & IOBIT_MESSAGE) {
		if (iShowFacility) std::cout << "(" << facility << ") ";
		std::cout << text << std::endl;
	}
}
void IO::notice (std::string const& facility, std::string const& text) const {
	if (iFlags & IOBIT_NOTICE) {
		if (iShowFacility) std::cout << "(" << facility << ")";
		if (iShowGroups && iShowFacility) std::cout << " ";
		if (iShowGroups) std::cout << "[Notice] ";
		std::cout << text << std::endl;
	}
}
void IO::warn   (std::string const& facility, std::string const& text) const {
	if (iFlags & IOBIT_WARN) {
		if (iShowFacility) std::cout << "(" << facility << ")";
		if (iShowGroups && iShowFacility) std::cout << " ";
		if (iShowGroups) std::cout << "[Warn] ";
		std::cout << text << std::endl;
	}
}
void IO::error  (std::string const& facility, std::string const& text) const {
	if (iFlags & IOBIT_ERROR) {
		if (iShowFacility) std::cout << "(" << facility << ")";
		if (iShowGroups && iShowFacility) std::cout << " ";
		if (iShowGroups) std::cout << "[Error] ";
		std::cout << text << std::endl;
	}

}
void IO::debug  (std::string const& facility, int level, std::string const& text)
	const {
	if (iFlags & IOBIT_DEBUG) {
		if (level <= iDebugLevel) {
			if (iShowFacility) std::cout << "(" << facility << ")";
			if (iShowGroups && iShowFacility) std::cout << " ";
			if (iShowGroups) std::cout << "[Debug" << level << "] ";
			std::cout << text << std::endl;
		}
	}
}

