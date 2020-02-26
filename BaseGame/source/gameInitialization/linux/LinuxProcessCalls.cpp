#ifdef __linux__

#include "LinuxProcessCalls.h"

#include<iostream> // cout, endl
#include <string> // string

#include <dirent.h> //readdir, opendir, DIR, DT_DIR, dirent
#include <string.h> // strcasestr

#include "../../utilities/StringUtils.h"
#include "../../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include "../../utilities/Templates.h"

#include <boost/filesystem.hpp> // path, file_status, is_directory, filesystem_error, directory_iterator, exists, directory_entry
#include <boost/filesystem/fstream.hpp> // ifstream
#include <boost/algorithm/string/trim.hpp> // trim
#include <boost/algorithm/string.hpp> // split, is_any_of, to_lower

#include <vector> // vector;

using boost::filesystem::path;
using boost::filesystem::file_status;

using boost::filesystem::exists;
using boost::filesystem::is_directory;
using boost::filesystem::is_regular_file;

using boost::filesystem::filesystem_error;
using boost::filesystem::directory_iterator;
using boost::filesystem::directory_entry;

using boost::filesystem::ifstream;

using std::string;
using std::stringstream;
using std::vector;

using boost::algorithm::trim;

using boost::algorithm::split;
using boost::algorithm::is_any_of;
//using boost::algorithm::to_lower;

namespace base_game {
	LinuxProcessCalls::LinuxProcessCalls() {
		logger::trace("Create LinuxProcessCalls");
	}

	LinuxProcessCalls::~LinuxProcessCalls() {
		logger::trace("Destroy LinuxProcessCalls");
	}

//TODO: When running from CodeBlocks isOnlyInstance recognizes nautilus sessions. When Nautilus is opened on ..\Watermill folder, it is treated as application instance
	bool LinuxProcessCalls::isOnlyInstance(const string& gameTitle) {
		stringstream ss;

		int howManyGames = 0;
		path procPath {"/proc/"};

		try {
			//file_status fileStatus = status(procPath);

			if (exists(procPath) && is_directory(procPath)) {
			} else {

				ss << "Couldn't open the " + procPath.string() + " directory";

				logger::error(ss);
				return false;
			}

			directory_iterator dirIterator {procPath};
			while (dirIterator != directory_iterator {}) {
				directory_entry dirEntry = *dirIterator;

				string lastDir = dirEntry.path().filename().string();

				if (string_utils::isStringNumeric(lastDir)) {
					path cmdPath = dirEntry.path() / path("cmdline");

					if (exists(cmdPath) && is_regular_file(cmdPath)) {

						ifstream cmdFile;

						cmdFile.open(cmdPath, std::ios::in);
						string strCmdline;

						if (cmdFile) {

							while (getline(cmdFile, strCmdline)) {

								vector<string> vectorCmd;
								split(vectorCmd, strCmdline, is_any_of("/"));

								if (!vectorCmd.empty()) {
									string lastVectorElement;

									lastVectorElement = vectorCmd[vectorCmd.size()
									- 1];

									if (string_utils::doesStringContainsIgnoreCase(
													lastVectorElement, gameTitle)) {

										howManyGames++;

									}
								}

							}
						}

					}
				}

				dirIterator++;
			}

		} catch (filesystem_error &error) {

			ss << "Error: " << error.what();
			logger::error(ss);
		}


		if (howManyGames >= 2) {
			// First process is this process
			// Second process is second game process
			return false;
		}

		else {
			return true;
		}

	}
}

#endif /* __linux__ */
