#ifndef DEBUGGINGOPTIONS_H
#define DEBUGGINGOPTIONS_H

#include <string>
#include <map> // std::map
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
class DebuggingOptions {
public:
	const static std::string ASSETS_READ_MODE;

	const static std::string ASSETS_SAVE_MODE;

	DebuggingOptions();
	virtual ~DebuggingOptions();
	void load(const std::string &filename);
	std::string getOption(const std::string &key);
protected:

private:
	const static std::string DEBUG_NODE_NAME;
	const static std::string OPTIONS_NODE_NAME;
	const static std::string OPTION_NODE_NAME;
	const static std::string OPTION_NAME_ATTR;
	const static std::string OPTION_VALUE_ATTR;
	std::map<std::string, std::string> options;

	void loadAttrNode(const boost::property_tree::ptree& xmlattrNode);

	void loadOptionNode(const boost::property_tree::ptree& optionNode);
	void loadOptionsNode(const boost::property_tree::ptree& optionsNode);
	void loadDebugNode(boost::property_tree::ptree tree);
	void loadRootNode(boost::property_tree::ptree tree);

	void loadMain(const std::string &filename);

};
}

#endif // DEBUGGINGOPTIONS_H
