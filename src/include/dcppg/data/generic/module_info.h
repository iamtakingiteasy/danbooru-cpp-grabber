#ifndef DCPPG_DATA_GENERIC_MODULEINFO_H
#define DCPPG_DATA_GENERIC_MODULEINFO_H

typedef enum {
    ML_NONE,
    ML_C,
    ML_CPP
} ModuleLang;

typedef enum {
    MT_NONE,
    MT_CORE,
    MT_DOWNLOADER,
    MT_PARSER,
    MT_HANDLER
} ModuleType;

typedef struct {
	ModuleLang lang;
	ModuleType type;
	char const* name;
	char const* descr;
	char const* version;
	char const* author;
} ModuleInfo;

#endif
