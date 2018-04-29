#include "DefaultResourceLoader.h"
#include "../debugging/Logger.h"

#include <string> // string
using std::string;

namespace base_game {
DefaultResourceLoader::DefaultResourceLoader()
{
   logger::trace("Create DefaultResourceLoader");
}

DefaultResourceLoader::~DefaultResourceLoader()
{
    logger::trace("Destroy DefaultResourceLoader");
}

string DefaultResourceLoader::vGetPattern() {
	return "*";
}
}
