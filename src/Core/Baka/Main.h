#ifndef DANBOORU_CPP_GRABBER_CORE_MAIN
#define DANBOORU_CPP_GRABBER_CORE_MAIN

#include "Logger.h"
#include "Core.h"
#include "ModuleManager.h"

#include <danbooru-cpp-grabber/Generic/Stringify.h>

#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>

extern Logger log;
extern Core core;

int main(int argc, char ** argv);
void help();
void parseArguments(int argc, char ** argv);
void makeInstances();
void validate();

#endif
