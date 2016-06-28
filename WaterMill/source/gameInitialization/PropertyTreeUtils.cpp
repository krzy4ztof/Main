#include "PropertyTreeUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <iostream> // cout, endl

using namespace std;

namespace watermill {
	PropertyTreeUtils::PropertyTreeUtils() {
		//ctor
	}

	PropertyTreeUtils::~PropertyTreeUtils() {
		//dtor
	}

	namespace property_tree_utils {
		const boost::property_tree::ptree& empty_ptree() {
			static boost::property_tree::ptree propertyTree;
			return propertyTree;
		}


		string printValueType(const std::string& s) {
			return "\"" + s + "\"";
		};

		void print_tree(const boost::property_tree::ptree& propertyTree, int level) {
			const std::string sep(2 * level, ' ');
			for(const boost::property_tree::ptree::value_type &valueType: propertyTree) {
				std::cout
						<< sep
						<< printValueType(valueType.first) << " : " << printValueType(valueType.second.data()) << "\n";
				print_tree(valueType.second, level + 1);
			}
		}
	}
}
