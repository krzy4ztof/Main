#include "SaveManager.h"

#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream, std::stringbuf
#include <boost/filesystem.hpp>// path
#include <vector> // vector
#include "../utilities/StringUtils.h"

using std::string;
using std::stringstream;
using std::vector;

using boost::filesystem::path;
using boost::filesystem::status;
using boost::filesystem::exists;
using boost::filesystem::file_status;
using boost::filesystem::create_directory;
using boost::filesystem::filesystem_error;


namespace base_game {
	SaveManager::SaveManager() {
		logger::trace("Create SaveManager");
		savePath = nullptr;
	}

	SaveManager::~SaveManager() {
		logger::trace("Destroy SaveManager");
		if(savePath) {
			delete(savePath);
		}
	}

	void SaveManager::init(string userProfile, string gameAppDir) {

		stringstream ss;
		vector <string> foldersVector;

		ss << "SaveManager saveGame: " << gameAppDir;
		logger::trace(ss);
		ss << "SaveManager userProfilePathStr: " << userProfile;
		logger::trace(ss);

		savePath = new path(userProfile);

		string_utils::splitString ( foldersVector, gameAppDir, '\\' );
		for (string folder : foldersVector) {
			ss << "folder: " << folder;
			logger::trace(ss);
			*savePath /= folder;
			ss << "path: " << *savePath;
			logger::trace(ss);


			file_status st = status(*savePath);
			ss << "path exists: " << exists(st);
			logger::trace(ss);

			if (!exists(st)) {
				try {
					if (create_directory(*savePath)) {
						ss << "path created: " << *savePath;
						logger::trace(ss);
					}
				} catch (filesystem_error &e) {
					ss << e.what();
					logger::error(ss);
				}
			}
		}
	}
}
