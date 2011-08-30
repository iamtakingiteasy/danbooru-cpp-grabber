#include "Logger.h"

void Logger::io(IO const* iio) {
	iIO = iio;
}
void Logger::facility(std::string const& facility) {
	iFacility = facility;
}


void Logger::message(std::string const& text) const {
	iIO->message(iFacility,text);
}
void Logger::notice (std::string const& text) const {
	iIO->notice(iFacility,text);
}
void Logger::warn   (std::string const& text) const {
	iIO->warn(iFacility,text);
}
void Logger::error  (std::string const& text) const {
	iIO->error(iFacility,text);
}
void Logger::debug  (int level, std::string const& text) const {
	iIO->debug(iFacility,level,text);
}
