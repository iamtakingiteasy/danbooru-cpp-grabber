#include "CLI.h"

extern "C" std::string const moduleType = "interface";
extern "C" std::string const moduleName = "CLI";
extern "C" std::string const moduleDescr = "Command Line Interface";
extern "C" std::string const moduleVersion = "1.0";
extern "C" std::string const moduleAuthor = "Alexander <itakingiteasy> Tumin";

extern "C" CLIInterface * create() { return new CLIInterface; }
extern "C" void destroy(CLIInterface *ptr) { delete ptr; }


void CLIInterface::init(Hash * o, Logger * l) {
}

void CLIInterface::hListAll(std::string const& arg, void * usr) {
	
}

std::vector<Option> CLIInterface::getOptions() {
	std::vector<Option> options;
	options.push_back(Option(this,hListAll,"la","list-all","",
					"Lists all modules"));
	return options;
}


void CLIInterface::interact() {
	
}

void CLIInterface::deinit() {
}
		
