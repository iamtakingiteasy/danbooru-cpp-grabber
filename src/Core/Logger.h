#ifndef DCCPG_CORE_LOGGER_H
#define DCPPG_CORE_LOGGER_H


class Logger {
	private:
		Logger() {}
		~Logger() {}
	public:
		void message(std::string const& text);
		void notice (std::string const& text);
		void warn   (std::string const& text);
		void error  (std::string const& text);
		void debug  (int level, std::string const& text);
};

#endif
