#ifndef DEFAULTRESOURCELOADER_H
#define DEFAULTRESOURCELOADER_H

#include "IResourceLoader.h"

namespace base_game {
class DefaultResourceLoader: public IResourceLoader
{
    public:
        DefaultResourceLoader();
        virtual ~DefaultResourceLoader();

    protected:

    private:
};
}

#endif // DEFAULTRESOURCELOADER_H
