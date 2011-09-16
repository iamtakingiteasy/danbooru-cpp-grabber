#ifndef DCPPG_DATA_GENERIC_MODULEINFO_H
#define DCPPG_DATA_GENERIC_MODULEINFO_H

typedef enum {
    MT_CORE,
    MT_MANAGER,
    MT_DOWNLOADER,
    MT_PARSER,
    MT_HANDLER
} ModuleType;

typedef struct {
	ModuleType type;
	char const* name;
	char const* descr;
	char const* version;
	char const* author;
} ModuleInfo;

#endif
