#include "InitOptions.h"
#include "ErrorCode.h"
#include "../utilities/PropertyTreeUtils.h"

// TODO: remove
//#include <dirent.h> //readdir, opendir, DIR, DT_DIR, dirent

#include <string> // string
#include <iostream> // cout, endl
#include <fstream> // ifstream
#include "boost/filesystem.hpp" //

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "../debugging/Logger.h"

using std::string;
using std::ifstream;

namespace base_game {

const string InitOptions::INIT_FILENAME = "watermill.ini";
const string InitOptions::ASSETS_FOLDER = "MAIN.Assets";
const string InitOptions::GAME_FOLDER = "MAIN.Game";
const string InitOptions::ROOT_FOLDER = "MAIN.Root";

string InitOptions::getAssetsFolder() {
	return assetsFolder;
}

string InitOptions::getGameFolder() {
	return gameFolder;
}

string InitOptions::getRootFolder() {
	return rootFolder;
}

void InitOptions::readFile(const string &filename) {
	boost::property_tree::ptree tree;
	boost::property_tree::read_ini(filename, tree);
	property_tree_utils::print_tree(tree, 0);

	boost::optional<boost::property_tree::ptree&> rootTree =
			tree.get_child_optional(ROOT_FOLDER);

	if (rootTree.is_initialized()) {
		rootFolder = rootTree.get().get_value<string>();
		//resources = resourcesTree.get_value<string>();
		logger::trace("istnieje MAIN.REsources");
		logger::trace(rootFolder);
	} else {
		string errorMessage = "There is no " + ROOT_FOLDER + " value in "
				+ INIT_FILENAME;
		throw ErrorCode(errorMessage, 111);
	}

	boost::optional<boost::property_tree::ptree&> assetsTree =
			tree.get_child_optional(ASSETS_FOLDER);

	if (assetsTree.is_initialized()) {
		assetsFolder = assetsTree.get().get_value<string>();
		//resources = resourcesTree.get_value<string>();
		logger::trace("istnieje MAIN.REsources");
		logger::trace(assetsFolder);
	} else {
		string errorMessage = "There is no " + ASSETS_FOLDER + " value in "
				+ INIT_FILENAME;
		throw ErrorCode(errorMessage, 111);
	}

	boost::optional<boost::property_tree::ptree&> gameTree =
			tree.get_child_optional(GAME_FOLDER);

	if (gameTree.is_initialized()) {
		gameFolder = gameTree.get().get_value<string>();
		//resources = resourcesTree.get_value<string>();
		logger::trace("istnieje MAIN.REsources");
		logger::trace(gameFolder);
	} else {
		string errorMessage = "There is no " + GAME_FOLDER + " value in "
				+ INIT_FILENAME;
		throw ErrorCode(errorMessage, 111);
	}

}

void InitOptions::checkFile(const string &filename) {

	ifstream myfile(filename);

	if (myfile.is_open()) {
		logger::trace("otwarte!!!!");
		myfile.close();

		readFile(filename);

	} else {
		logger::trace("NIE otwarte!!!!");

		const boost::filesystem::path& initialPath =
				boost::filesystem::initial_path();

		string errorMessage = "There is no " + INIT_FILENAME + " in "
				+ initialPath.string() + " folder ";
		throw ErrorCode(errorMessage, 111);

	};
}

InitOptions::InitOptions() {
	logger::trace("Create InitOptions");

	// Initialization
	bool somethingWentWrong = false;

	checkFile(INIT_FILENAME);
	//		checkCurDir();

	if (somethingWentWrong) {
		throw ErrorCode("INIT_OPTIONS_PROBLEM", 789);
	}
}

InitOptions::~InitOptions() {
	logger::trace("Destroy InitOptions");
}

}
