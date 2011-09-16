#ifndef DCPPG_DATA_CPPSPECIFIC_OPTION_HPP
#define DCPPG_DATA_CPPSPECIFIC_OPTION_HPP

#include <dcppg/data/generic/option.h>



class OptionWrapper {
    private:
	Option opt;
    public:
	OptionWrapper() {
	    opt.domain = NULL;
	    opt.odescr = NULL;
	    opt.oshort = NULL;
	    opt.olong  = NULL;
	    opt.oarg   = NULL;
	    opt.source = NULL;
	    opt.value  = 0;
	    opt.processor = NULL;
	}
	OptionWrapper(char const* odescr
		      ,char const* oshort
		      ,char const* olong
		      ,char const* oarg
		      ,void * source
		      ,int value
		      ,char (*processor)(void *, void *)) {
	    opt.domain = NULL;
	    opt.odescr = odescr;
	    opt.oshort = oshort;
	    opt.olong  = olong;
	    opt.oarg   = oarg;
	    opt.source = source;
	    opt.value  = value;
	    opt.processor = processor;
	}	
	~OptionWrapper() {
	}
    public:
	Option get_opt() {
	    return opt;
	}
};

#endif
