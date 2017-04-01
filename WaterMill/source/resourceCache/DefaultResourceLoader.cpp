#include "DefaultResourceLoader.h"
#include "../debugging/Logger.h"

namespace base_game {
DefaultResourceLoader::DefaultResourceLoader()
{
   logger::trace("Create DefaultResourceLoader");
}

DefaultResourceLoader::~DefaultResourceLoader()
{
    logger::trace("Destroy DefaultResourceLoader");
}
}
