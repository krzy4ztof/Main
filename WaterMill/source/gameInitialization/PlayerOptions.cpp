#include "PlayerOptions.h"

#include "PropertyTreeUtils.h"

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

using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::map;
using std::iterator;
using std::out_of_range;

namespace watermill {

	const string PlayerOptions::LANGUAGE = "language";

	const string PlayerOptions::PLAYER_OPTIONS_NODE_NAME = "playerOptions";
	const string PlayerOptions::OPTION_NODE_NAME = "option";
	const string PlayerOptions::OPTION_NAME_ATTR = "name";
	const string PlayerOptions::OPTION_VALUE_ATTR = "value";

	namespace player_options {
		void safe_delete(PlayerOptions* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}

	PlayerOptions::PlayerOptions() {
		//ctor
	}

	PlayerOptions::~PlayerOptions() {
		//dtor
	}


	void PlayerOptions::loadAttrNode(const boost::property_tree::ptree& xmlattrNode) {

		string attrName;
		string attrValue;
		for(const boost::property_tree::ptree::value_type & xmlAttrChild: xmlattrNode) {
			string key = xmlAttrChild.first;
			string value = xmlAttrChild.second.data();

			if (key.compare(OPTION_NAME_ATTR) == 0) {
				attrName = value;
			} else if (key.compare(OPTION_VALUE_ATTR) == 0) {
				attrValue = value;
			}

			if (!attrName.empty() && !attrValue.empty()) {
				pair<string,string> optionPair = make_pair(attrName,attrValue);
				options.insert(optionPair);
			}
		}
	}

	void PlayerOptions::loadOptionNode(const boost::property_tree::ptree& optionNode) {
		for(const boost::property_tree::ptree::value_type & optionChild: optionNode) {
			string name = optionChild.first;
			int compRes = name.compare("<xmlattr>");
			if (compRes == 0) {
				loadAttrNode(optionChild.second);
			}
		}
	}

	void PlayerOptions::loadPlayerOptionsNode(boost::property_tree::ptree playerOptionsNode) {
		for (const boost::property_tree::ptree::value_type& playerOptionsChild : playerOptionsNode) {
			string name = playerOptionsChild.first.data();
			int compRes = name.compare(OPTION_NODE_NAME);

			if (compRes == 0) {
				loadOptionNode(playerOptionsChild.second);
			}
		}
	}


	void PlayerOptions::loadRootNode(boost::property_tree::ptree tree) {
		// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree_fwd.hpp
		// typedef basic_ptree<std::string, std::string> ptree;


		// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree.hpp
		// typedef basic_ptree<Key, Data, KeyCompare> self_type;
		// typedef std::pair<const Key, self_type>      value_type;
		// value_type = pair<std::string, basic_ptree<std::string. std::string>>

		for (const boost::property_tree::ptree::value_type& rootChildNode : tree) {
			string name = rootChildNode.first;
			int compRes = name.compare(PLAYER_OPTIONS_NODE_NAME);
			if (compRes == 0) {
				loadPlayerOptionsNode(rootChildNode.second);
			}
		}
	}

	string PlayerOptions::getOption(const string &key) {
		try {
			return options.at(key);
		} catch (out_of_range& ex) {
			cout << "Exception: " << ex.what() << endl;
		}
		return "UNSET";
	}

	void PlayerOptions::loadMain(const string &filename) {
		boost::property_tree::ptree tree;
		boost::property_tree::read_xml(filename, tree);
		property_tree_utils::print_tree(tree,0);

		loadRootNode(tree);
		map<string, string>::iterator optionsIterator;

		for (optionsIterator = options.begin(); optionsIterator!=options.end(); optionsIterator++) {
			cout << "Option: " << optionsIterator->first << " => " << optionsIterator->second << endl;
		}
	}

	void PlayerOptions::load(const string &filename) {
		loadMain(filename);
	}
}
