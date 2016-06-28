#include "DebuggingOptions.h"
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


using namespace std;
// std::string

namespace watermill {

	const string DebuggingOptions::DEBUG_NODE_NAME = "debug";
	const string DebuggingOptions::OPTIONS_NODE_NAME = "options";
	const string DebuggingOptions::OPTION_NODE_NAME = "option";
	const string DebuggingOptions::OPTION_NAME_ATTR = "name";
	const string DebuggingOptions::OPTION_VALUE_ATTR = "value";

	DebuggingOptions::DebuggingOptions() {
		//ctor
	}

	DebuggingOptions::~DebuggingOptions() {
		//dtor
	}


	void DebuggingOptions::loadAttrNode(const boost::property_tree::ptree& xmlattrNode) {

		for(const boost::property_tree::ptree::value_type & xmlAttrChild: xmlattrNode) {
			cout << "          XmlAttr First: " << xmlAttrChild.first.data() << "; XmlAttr Second: " << xmlAttrChild.second.data() << endl;
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
				cout << "INSERTED OPTION: " << attrName << " : " << attrValue << endl;
			}



			cout << "          XmlAttr Key: " << key << "; XmlAttr Value: " << value << endl;
		}
	}

	void DebuggingOptions::loadOptionNode(const boost::property_tree::ptree& optionNode) {
		for(const boost::property_tree::ptree::value_type & optionChild: optionNode) {
			string name = optionChild.first;
			int compRes = name.compare("<xmlattr>");
			cout << "compRes3: " << name << " to -> "  << compRes << endl;
			if (compRes == 0) {
				loadAttrNode(optionChild.second);
			}
		}
	}

	void DebuggingOptions::loadOptionsNode(const boost::property_tree::ptree& optionsNode) {
		for(const boost::property_tree::ptree::value_type & optionsChild: optionsNode) {
			string name = optionsChild.first;
			int compRes = name.compare(OPTION_NODE_NAME);
			cout << "compRes2: " << name << " to -> "  << compRes << endl;

			if (compRes == 0) {
				loadOptionNode(optionsChild.second);
			}
		}
	}

	void DebuggingOptions::loadDebugNode(boost::property_tree::ptree debugNode) {
		for (const boost::property_tree::ptree::value_type& debugChild : debugNode) {
			string name = debugChild.first.data();
			int compRes = name.compare(OPTIONS_NODE_NAME);
			cout << "compRes: " << name << " to -> "  << compRes << endl;

			if (compRes == 0) {
				loadOptionsNode(debugChild.second);
			}
		}
	}


	void DebuggingOptions::loadRootNode(boost::property_tree::ptree tree) {
		// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree_fwd.hpp
		// typedef basic_ptree<std::string, std::string> ptree;


		// see C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\boost\property_tree\ptree.hpp
		// typedef basic_ptree<Key, Data, KeyCompare> self_type;
		// typedef std::pair<const Key, self_type>      value_type;
		// value_type = pair<std::string, basic_ptree<std::string. std::string>>

		for (const boost::property_tree::ptree::value_type& rootChildNode : tree) {
			string name = rootChildNode.first;
			int compRes = name.compare(DEBUG_NODE_NAME);
			cout << "root compRes: " << name << " to -> "  << compRes << endl;
			if (compRes == 0) {
				loadDebugNode(rootChildNode.second);
			}
		}
	}

		try {
			return options.at(key);
		} catch (out_of_range& ex) {
			cout << "Exception: " << ex.what() << endl;
		}
		return "UNSET";
	}

	void DebuggingOptions::loadMain(const string &filename) {
		boost::property_tree::ptree tree;
		boost::property_tree::read_xml(filename, tree);
		property_tree_utils::print_tree(tree,0);

		loadRootNode(tree);


		map<string, string>::iterator optionsIterator;

		for (optionsIterator = options.begin(); optionsIterator!=options.end(); optionsIterator++) {
			cout << "Option: " << optionsIterator->first << " => " << optionsIterator->second << endl;
		}

		cout << getOption("Jakas opcja") << endl;
		cout << getOption("hardwareAcceleration") << endl;

	}

	void DebuggingOptions::load(const string &filename) {
		cout << "xml fileName: " << filename << endl;
		//checkCurDir();
		//checkFile(filename);
		//loadDebug(filename);
		//		loadPets(filename);
		//loadOptions(filename);

		loadMain(filename);


	}
}
