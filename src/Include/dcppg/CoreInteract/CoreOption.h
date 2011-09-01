#ifndef DCPPG_CORE_INTERACT_OPTIONS_H
#define DCPPG_CORE_INTERACT_OPTIONS_H

class CoreOption {
	public:
		virtual ~CoreOption() {}
	public:
		virtual void collectOpts() = 0;
		virtual void parseOpts() = 0;
		virtual std::string const& genHelp() = 0;
		virtual void ignoreUnknown(bool) = 0;
		virtual void facilize(bool) = 0;
		virtual void group(bool) = 0;
		virtual void facilizeSwitch() = 0;
		virtual void groupSwitch() = 0;
		virtual void width(size_t) = 0;

};

#endif
