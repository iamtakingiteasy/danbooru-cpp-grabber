#include "CoreLogger.h"


void CoreLogger::setFacility(std::string const& f) {
	facility = f;
}
void CoreLogger::setRealLogger(Logger const* l) {
	log = l;
}


void CoreLogger::message(std::string const& text) const {
	log->message(facility,text);
}
void CoreLogger::notice (std::string const& text) const {
	log->notice(facility,text);
}
void CoreLogger::warn   (std::string const& text) const {
	log->warn(facility,text);
}
void CoreLogger::error  (std::string const& text) const {
	log->error(facility,text);
}
void CoreLogger::debug  (int level, std::string const& text) const {
	log->debug(facility,level,text);
}
