#include "grabber.hpp"


void Grabber::run(int ac, char ** av) {
    grabber_init(ac,av);
    option_parser.scanner(modules_options);
    std::cout << option_parser.gen_help();
}

