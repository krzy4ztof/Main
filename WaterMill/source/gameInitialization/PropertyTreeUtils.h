#ifndef PROPERTYTREEUTILS_H
#define PROPERTYTREEUTILS_H

#include <string> // string
#include <boost/property_tree/ptree.hpp>

namespace watermill {
	class PropertyTreeUtils {
		public:
			PropertyTreeUtils();
			virtual ~PropertyTreeUtils();

		protected:

		private:

	};

	namespace property_tree_utils {
		const boost::property_tree::ptree& empty_ptree();
		void print_tree(const boost::property_tree::ptree& propertyTree, int level);
	}

}
#endif // PROPERTYTREEUTILS_H
