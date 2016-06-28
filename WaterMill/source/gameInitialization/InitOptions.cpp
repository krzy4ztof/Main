#include "InitOptions.h"
#include "ErrorCode.hpp"
#include "PropertyTreeUtils.h"

// TODO: remove
//#include <dirent.h> //readdir, opendir, DIR, DT_DIR, dirent

#include <string> // string
#include <iostream> // cout, endl
#include <fstream> // ifstream
#include "boost/filesystem.hpp" //

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;
// std::string

namespace watermill {

	const string InitOptions::INIT_FILENAME = "watermill.ini";
	const string InitOptions::RESOURCES_FOLDER = "MAIN.Resources";

	string InitOptions::getResourcesFolder() {
		return resourcesFolder;
	}

	void InitOptions::readFile(const string &filename) {
		boost::property_tree::ptree tree;
		boost::property_tree::read_ini(filename, tree);
		property_tree_utils::print_tree(tree,0);

		boost::optional<boost::property_tree::ptree&> resourcesTree = tree.get_child_optional(RESOURCES_FOLDER);


		if (resourcesTree.is_initialized()) {
			resourcesFolder =     resourcesTree.get().get_value<string>();
			//resources = resourcesTree.get_value<string>();
			cout << "istnieje MAIN.REsources" << endl;
			cout << resourcesFolder << endl;
		} else {
			string errorMessage = "There is no " +  RESOURCES_FOLDER + " value in " + INIT_FILENAME;
			throw ErrorCode(errorMessage, 111 );
		}

	}

	void InitOptions::checkFile(const string &filename) {

		ifstream myfile(filename);

		if ( myfile.is_open() ) {
			cout << "otwarte!!!!" <<endl;
			myfile.close();

			readFile(filename);

		} else {
			cout << "NIE otwarte!!!!" <<endl;

			const boost::filesystem::path& initialPath = boost::filesystem::initial_path();

			string errorMessage = "There is no " + INIT_FILENAME + " in " + initialPath.string() + " folder ";
			throw ErrorCode(errorMessage, 111 );

		};
	}

	InitOptions::InitOptions() {

		// Initialization
		bool somethingWentWrong = false;


		checkFile(INIT_FILENAME);
		//		checkCurDir();

		if (somethingWentWrong) {
			throw ErrorCode("INIT_OPTIONS_PROBLEM", 789);
		}
	}

	InitOptions::~InitOptions() {
		//dtor
	}

}
