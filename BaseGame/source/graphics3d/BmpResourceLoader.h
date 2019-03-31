/*
 * BmpResourceLoader.h
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_BMPRESOURCELOADER_H_
#define GRAPHICS3D_BMPRESOURCELOADER_H_

#include "../graphics3d/TextureResourceLoader.h"
#include "../resourceCache/IResourceLoader.h"
#include "../resourceCache/ResourceHandle.h"

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <string> // string
#include <memory> // shared_ptr

namespace base_game {

class BmpResourceLoader: public TextureResourceLoader {
public:
	BmpResourceLoader();
	virtual ~BmpResourceLoader();

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle); // ????

	virtual std::string vGetPattern();
};

} /* namespace base_game */

#endif /* GRAPHICS3D_BMPRESOURCELOADER_H_ */
