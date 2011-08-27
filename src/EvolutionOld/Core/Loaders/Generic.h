#ifndef DANBOORU_CPP_GRABBER_CORE_LOADER_GENERIC
#define DANBOORU_CPP_GRABBER_CORE_LOADER_GENERIC

#include <string>
#include <vector>
#include <danbooru-cpp-grabber/Generic/OptParser.h>
#include "Modular.h"

class GenericLoader {
	protected:
		Modular moduleHandle;
	protected:
		std::string name;
		std::string description;
		std::string version;
		std::string author;
	public:
		GenericLoader() {}
		virtual ~GenericLoader() {}
	public:
		void loadGeneric(std::string const& filepath);
	public:
		bool isLoaded() const;
		std::string const& getName()        const;
		std::string const& getDescription() const;
		std::string const& getVersion()     const;
		std::string const& getAuthor()      const;
		std::string const& getOptions()     const;
};

#endif
