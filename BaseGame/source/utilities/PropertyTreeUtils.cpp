#include "PropertyTreeUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <iostream> // cout, endl
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using std::cout;
using std::endl;
using std::stringstream;

namespace base_game {

	namespace property_tree_utils {
		const boost::property_tree::ptree& empty_ptree() {
			static boost::property_tree::ptree propertyTree;
			return propertyTree;
		}


		string printValueType(const string& s) {
			return "\"" + s + "\"";
		};

		void print_tree(const boost::property_tree::ptree& propertyTree, int level) {
			const string sep(2 * level, ' ');
			for(const boost::property_tree::ptree::value_type &valueType: propertyTree) {
				stringstream ss;
				ss << sep << printValueType(valueType.first) << " : " << printValueType(valueType.second.data());
		logger::trace(ss);

				print_tree(valueType.second, level + 1);
			}
		}
	}
}
