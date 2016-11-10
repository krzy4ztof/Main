#include "ResourceZipFile.h"
#include "../debugging/Logger.h"

#include <string>

using std::string;

namespace base_game {
	ResourceZipFile::ResourceZipFile(const string fileName) {
		logger::trace("Create ResourceZipFile");
	}

	ResourceZipFile::~ResourceZipFile() {
		logger::trace("Destroy ResourceZipFile");
	}
}
