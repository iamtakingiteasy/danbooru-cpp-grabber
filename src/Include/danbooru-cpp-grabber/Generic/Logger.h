#ifndef DANBOORU_CPP_GRABBER_CORE_LOGGER
#define DANBOORU_CPP_GRABBER_CORE_LOGGER

#include "Config.h"
#include <string>
#include <iostream>

class Logger {
	private:
		Config * conf;
		std::string facility;
	public:
		Logger(Config * c, std::string const& facility) :
			conf(c),
			facility(facility)
		{}
	public:
		void message(std::string const& text) const {
			if (conf->verbose & VL_MESSAGE) {
				std::cout << facility << text << std::endl;
			}
		}

		void notice(std::string const& text) const {
			if (conf->verbose & VL_NOTICE) {
				std::cout << facility << "[Notice] " << text << std::endl;
			}
		}
		void warn(std::string const& text) const {
			if (conf->verbose & VL_WARN) {
				std::cout << facility << "[Warning] " << text << std::endl;
			}
		}

		void error(std::string const& text) const {
			if (conf->verbose & VL_ERROR) {
				std::cout << facility << "[Error] " << text << std::endl;
			}
		}
		
		void debug(int level, std::string const& text) const {
			if (conf->verbose & VL_DEBUG) {
				if (level <= conf->debugLevel) {
					std::cout << facility
							  << "[Debug["
							  << level
							  << "]] "
							  << text
							  << std::endl;
				}
			}
		}

};

#endif
