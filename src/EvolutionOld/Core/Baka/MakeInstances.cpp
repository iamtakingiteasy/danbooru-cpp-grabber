#include "Main.h"

void makeInstances() {
	bool wasError = false;

	if (!core.downloaders[core.downloaderName].isLoaded()) {
		int index = atoi(core.downloaderName.c_str());
		if (index <= 0) {
			wasError = true;
			log.error(
				"No downloader with name "
				+ core.downloaderName
				+ " found. Try -dl");
		} else {
			index -= 1;
			if (!core.downloaders[core.downloadersIndex[index]].isLoaded()) {
				wasError = true;
				log.error(
					"No downloader with index "
					+ Stringify(index + 1).str()
					+ " found. Try -dl");
			} else {
				core.downloaderInstance
					= core.downloaders[core.downloadersIndex[index]].create();
			}
		}
	} else {
		core.downloaderInstance = core.downloaders[core.downloaderName].create();
	}

	
	if (wasError) {
		exit(-1);
	}
}
