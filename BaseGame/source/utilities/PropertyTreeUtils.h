#ifndef PROPERTYTREEUTILS_H
#define PROPERTYTREEUTILS_H

#include <string> // string
#include <boost/property_tree/ptree.hpp>

namespace base_game {

namespace property_tree_utils {
const boost::property_tree::ptree& empty_ptree();
void print_tree(const boost::property_tree::ptree& propertyTree, int level);
}

}
#endif // PROPERTYTREEUTILS_H
