#ifndef DCPPG_DATA_GENERIC_OPTION_H
#define DCPPG_DATA_GENERIC_OPTION_H

typedef struct {
	char const* domain;
	char const* odescr;
	char const* oshort;
	char const* olong;
	char const* oarg;
	void * source;
	int    value;
	char (*processor)(void *, void *);
} Option;

typedef struct {
	Option (*constructor)(
	    char const*,
	    char const*,
	    char const*,
	    char const*,
	    void *,
	    int,
	    char (*)(void *, void *)
	);
} OptionSymbols;

#endif
