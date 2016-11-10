#include "IResourceFile.h"
#include "../debugging/Logger.h"

namespace base_game {


	IResourceFile::~IResourceFile() {
		logger::info("Destroy IResourceFile");
	}
}
