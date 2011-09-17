#ifndef DCPPG_DATA_CPPSPECIFIC_OPTION_HPP
#define DCPPG_DATA_CPPSPECIFIC_OPTION_HPP

#include <dcppg/data/generic/option.h>

class CPPOption {
    private:
	Option opt;
    public:
	CPPOption()
	{
	    opt.odescr        = NULL;
	    opt.oshort        = NULL;
	    opt.olong         = NULL;
	    opt.oarg          = NULL;
	    opt.context       = NULL;
	    opt.default_value = 0;
	    opt.callback      = NULL;
		
	}
	CPPOption(
	    char const* odescr,
	    char const* oshort,
	    char const* olong,
	    char const* oarg,
	    void * context,
	    int default_value,
	    int (*callback)(void *, void*)
	)
	{
	    opt.odescr        = odescr;
	    opt.oshort        = oshort;
	    opt.olong         = olong;
	    opt.oarg          = oarg;
	    opt.context       = context;
	    opt.default_value = default_value;
	    opt.callback      = callback;
	}
    public:
	Option get() {
	    return opt;
	}
};

#endif
