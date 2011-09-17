#ifndef DCPPG_DATA_GENERIC_OPTION_H
#define DCPPG_DATA_GENERIC_OPTION_H


typedef struct {
	char const* odescr;
	char const* oshort;
	char const* olong;
	char const* oarg;
	void * context;
	int    default_value;
	int (*callback)(void *, void *);
} Option;

/* Structure for internal use by core only */
typedef struct {
	Option opt;
	char const* group;
	char const* name;
} Option__private__;


#endif
