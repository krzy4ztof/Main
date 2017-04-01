#include "ResourceZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

#include <string>

using std::string;

namespace base_game {
	ResourceZipFile::ResourceZipFile(const string fileName) {
		logger::info("Create ResourceZipFile");
		m_pZipFile = nullptr;
		m_resFileName = fileName;

	}

	ResourceZipFile::~ResourceZipFile() {
		logger::info("Destroy ResourceZipFile");
		templates::safe_delete<ZipFile>(m_pZipFile);

	}

	bool ResourceZipFile::vOpen() {
		m_pZipFile = new ZipFile();
		if (m_pZipFile) {
			return m_pZipFile->init(m_resFileName);
		}
		return false;
	}
}
