#include "ResourceZipFile.h"
#include "../debugging/Logger.h"

#include <string>

using std::string;

namespace base_game {
	ResourceZipFile::ResourceZipFile(const string fileName) {
		logger::info("Create ResourceZipFile");
	}

	ResourceZipFile::~ResourceZipFile() {
		logger::info("Destroy ResourceZipFile");
	}
}
