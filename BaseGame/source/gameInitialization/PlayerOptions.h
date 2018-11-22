#ifndef PLAYEROPTIONS_H
#define PLAYEROPTIONS_H

#include <string>
#include <map> // std::map
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
	class PlayerOptions {
		public:
			const static std::string LANGUAGE;
	const static std::string LANGUAGES;


			PlayerOptions();
			virtual ~PlayerOptions();

			void load(const std::string &filename);
			std::string getOption(const std::string &key);
		protected:

		private:
			const static std::string PLAYER_OPTIONS_NODE_NAME;
			const static std::string OPTION_NODE_NAME;
			const static std::string OPTION_NAME_ATTR;
			const static std::string OPTION_VALUE_ATTR;
			std::map<std::string,std::string> options;

			void loadAttrNode(const boost::property_tree::ptree& xmlattrNode);

			void loadOptionNode(const boost::property_tree::ptree optionNode);
			void loadPlayerOptionsNode(boost::property_tree::ptree tree);
			void loadRootNode(boost::property_tree::ptree& tree);

			void loadMain(const std::string &filename);

	};
}
#endif // PLAYEROPTIONS_H
