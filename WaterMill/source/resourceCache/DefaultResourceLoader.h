#ifndef DEFAULTRESOURCELOADER_H
#define DEFAULTRESOURCELOADER_H

#include "IResourceLoader.h"
#include <string> // string

namespace base_game {
class DefaultResourceLoader: public IResourceLoader
{
    public:
        DefaultResourceLoader();
        virtual ~DefaultResourceLoader();

	virtual std::string vGetPattern();

    protected:

    private:
};
}

#endif // DEFAULTRESOURCELOADER_H
