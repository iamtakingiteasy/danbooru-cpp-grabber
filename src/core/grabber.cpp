#include "grabber.hpp"


void Grabber::run(int oargc, char ** oargv) {
    argc = oargc;
    for (int i = 0; i < argc; i++) {
	argv.push_back(oargv[i]);
    }
    grabber_init();
    gen_help(argc,argv.get_list(),modules_options.get_list());
}
