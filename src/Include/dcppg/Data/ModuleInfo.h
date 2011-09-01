#ifndef DCPPG_DATA_MODULE_INFO_H
#define DCPPG_DATA_MODULE_INFO_H

#include <dcppg/Data/Option.h>

#include <string>
#include <set>

class ModuleInfo {
	public:
		std::string type;
		std::string name;
		std::string author;
		std::string version;
		std::string descr;
		std::set<Option,Option::comparator> options;
	public:
		ModuleInfo() {}
		ModuleInfo(
			std::string const& name,
			std::string const& author,
			std::string const& version,
			std::string const& descr,
			std::set<Option,Option::comparator> options
		) :
			name(name),
			author(author),
			version(version),
			descr(descr),
			options(options)
		{}

};


#endif
