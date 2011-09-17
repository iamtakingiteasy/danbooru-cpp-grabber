#ifndef DCPPG_DATA_CPPSPECIFIC_MODULEINFO_HPP
#define DCPPG_DATA_CPPSPECIFIC_MODULEINFO_HPP

#include <dcppg/data/generic/module_info.h>

class CPPModuleInfo {
    private:
	ModuleInfo info;
    public:
	CPPModuleInfo()
	{
	    info.lang    = ML_NONE;
	    info.type    = MT_NONE;
	    info.name    = NULL;
	    info.descr   = NULL;
	    info.version = NULL;
	    info.author  = NULL;

	}
	CPPModuleInfo(
	    ModuleLang lang,
	    ModuleType type,
	    char const* name,
	    char const* descr,
	    char const* version,
	    char const* author
	)
	{
	    info.lang    = lang;
	    info.type    = type;
	    info.name    = name;
	    info.descr   = descr;
	    info.version = version;
	    info.author  = author;

	}
    public:
	ModuleInfo get() {
	    return info;
	}
};

#endif
