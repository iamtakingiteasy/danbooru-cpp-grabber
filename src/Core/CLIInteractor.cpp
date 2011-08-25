#include "Grabber.h"

#ifdef HAVE_IOCTL
#    include <sys/ioctl.h>
#endif


Grabber::Interactor::Interactor() {
	#ifdef HAVE_IOCTL
	struct winsize w;
	ioctl(0,TIOCGWINSZ,&w);
	opt.setTermWidth(w.ws_col);
	#endif

	opt.push_back("h", "help", "",
				  "This help message");
	
	opt.push_back("V", "version", "",
				  "Prints version info");
	
	opt.push_back("v", "verbose", "",
				  "Prints verbose (debug) info");
	
	opt.push_back("d", "download", "",
				  "Download selected tags");
	
	opt.push_back("u", "url", "",
				  "Specify URL of booru site");
	
	opt.push_back("mp","module-path", "DIR",
				  "Additional directory with plugins");
	
	opt.push_back("md","module-downloader","MODULE",
				  "Downloader module name or index");

	opt.push_back("mb","module-board", "MODULE",
				  "Board module name or index");
	
	opt.push_back("mh","module-handler", "MODULE",
				  "Handler module name or index");
	
	opt.push_back("so","search-order", "ORDER",
				  "Tag search resultsordering, one of 'count', 'name' or 'date'");
	
	opt.push_back("pl","page-limit","LIMIT",
				  "Page size limit");
	
	opt.push_back("po","page-offset","OFFSET",
				  "Page offset");

	opt.push_back("la","list-all","",
				  "List ALL modules");
		
	opt.push_back("ld","list-downloaders","",
				  "List downloader modules");
	
	opt.push_back("lb","list-boards","",
				  "List board modules");

	opt.push_back("lh","list-handlers","",
				  "List handler modules")
		;
	opt.push_back("C","working-directory","DIR",
				  "Change working directory before downloading");
}


void Grabber::Interactor::help() {
	opt.genHelp();
}
