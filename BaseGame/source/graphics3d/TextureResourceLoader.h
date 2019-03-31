/*
 * TextureResourceLoader.h
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_TEXTURERESOURCELOADER_H_
#define GRAPHICS3D_TEXTURERESOURCELOADER_H_

#include "../resourceCache/IResourceLoader.h"


#include <boost/cstdint.hpp> // boost::uintmax_t
#include <string> // string
#include <memory> // shared_ptr

namespace base_game {

class TextureResourceLoader: public IResourceLoader {
public:
	TextureResourceLoader();
	virtual ~TextureResourceLoader();

	virtual bool vUseRawFile();
	virtual bool vDiscardRawBufferAfterLoad();
	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize);

// TODO: gdzie to umiescic?
	//virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
	//		std::shared_ptr<ResourceHandle> handle); // ????


	// virtual std::string vGetPattern();

	/*
	 * 	virtual bool VUseRawFile() { return false; }
	 virtual bool VDiscardRawBufferAfterLoad() { return true; }
	 virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize);
	 virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, shared_ptr<ResHandle> handle);
	 */
};

} /* namespace base_game */

#endif /* GRAPHICS3D_TEXTURERESOURCELOADER_H_ */
