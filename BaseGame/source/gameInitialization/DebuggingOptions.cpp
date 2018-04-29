#include "DebuggingOptions.h"
#include "../utilities/PropertyTreeUtils.h"

#include <string> // string
#include <iostream> // cout, endl

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
// #include <boost/foreach.hpp>
#include <set>
#include <exception>

#include <map> // std::map
#include <utility> // std::pair
#include <stdexcept>      // std::out_of_range

#include <typeinfo> // typeid
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::stringstream;
using std::string;
using std::pair;
using std::out_of_range;
using std::map;
using std::iterator;

using boost::property_tree::ptree;
using value_type = boost::property_tree::ptree::value_type;
// typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using boost::property_tree::read_xml;

namespace base_game {

const string DebuggingOptions::DEBUG_NODE_NAME = "debug";
const string DebuggingOptions::OPTIONS_NODE_NAME = "options";
const string DebuggingOptions::OPTION_NODE_NAME = "option";
const string DebuggingOptions::OPTION_NAME_ATTR = "name";
const string DebuggingOptions::OPTION_VALUE_ATTR = "value";

const string DebuggingOptions::ASSETS_READ_MODE = "assetsReadMode";

const string DebuggingOptions::ASSETS_SAVE_MODE = "assetsSaveMode";

DebuggingOptions::DebuggingOptions() {
	logger::trace("Create DebuggingOptions");
}

DebuggingOptions::~DebuggingOptions() {
	logger::trace("Destroy DebuggingOptions");
}

void DebuggingOptions::loadAttrNode(const ptree& xmlattrNode) {

	string attrName;
	string attrValue;
	for (const value_type & xmlAttrChild : xmlattrNode) {
		string key = xmlAttrChild.first;
		string value = xmlAttrChild.second.data();

		if (key.compare(OPTION_NAME_ATTR) == 0) {
			attrName = value;
		} else if (key.compare(OPTION_VALUE_ATTR) == 0) {
			attrValue = value;
		}

		if (!attrName.empty() && !attrValue.empty()) {
			pair<string, string> optionPair = make_pair(attrName, attrValue);
			options.insert(optionPair);
		}
	}
}

void DebuggingOptions::loadOptionNode(const ptree& optionNode) {
	for (const value_type & optionChild : optionNode) {
		string name = optionChild.first;
		int compRes = name.compare("<xmlattr>");
		if (compRes == 0) {
			loadAttrNode(optionChild.second);
		}
	}
}

void DebuggingOptions::loadOptionsNode(const ptree& optionsNode) {
	for (const value_type & optionsChild : optionsNode) {
		string name = optionsChild.first;
		int compRes = name.compare(OPTION_NODE_NAME);

		if (compRes == 0) {
			loadOptionNode(optionsChild.second);
		}
	}
}

void DebuggingOptions::loadDebugNode(ptree debugNode) {
	for (const value_type& debugChild : debugNode) {
		string name = debugChild.first.data();
		int compRes = name.compare(OPTIONS_NODE_NAME);

		if (compRes == 0) {
			loadOptionsNode(debugChild.second);
		}
	}
}

void DebuggingOptions::loadRootNode(ptree tree) {
	// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree_fwd.hpp
	// typedef basic_ptree<std::string, std::string> ptree;

	// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree.hpp
	// typedef basic_ptree<Key, Data, KeyCompare> self_type;
	// typedef std::pair<const Key, self_type>      value_type;
	// value_type = pair<std::string, basic_ptree<std::string. std::string>>

	for (const value_type& rootChildNode : tree) {
		string name = rootChildNode.first;
		int compRes = name.compare(DEBUG_NODE_NAME);
		if (compRes == 0) {
			loadDebugNode(rootChildNode.second);
		}
	}
}

string DebuggingOptions::getOption(const string &key) {
	try {
		return options.at(key);
	} catch (out_of_range& ex) {
		stringstream ss;
		ss << "Exception: " << ex.what();
		logger::error(ss);
	}
	return "UNSET";
}

void DebuggingOptions::loadMain(const string &filename) {
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml(filename, tree);
	//	property_tree_utils::print_tree(tree,0);

	loadRootNode(tree);
	map<string, string>::iterator optionsIterator;

	//	for (optionsIterator = options.begin(); optionsIterator!=options.end(); optionsIterator++) {
	//		cout << "Option: " << optionsIterator->first << " => " << optionsIterator->second << endl;
	//	}
}

void DebuggingOptions::load(const string &filename) {
	//checkCurDir();
	//checkFile(filename);
	//loadDebug(filename);
	//		loadPets(filename);
	//loadOptions(filename);

	loadMain(filename);

}
}
