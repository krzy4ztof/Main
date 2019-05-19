/*
 * TextureResourceLoader.cpp
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#include "../graphics3d/TextureResourceLoader.h"

#include "../debugging/Logger.h"
#include <string> // string
#include <memory> // shared_ptr
#include <boost/cstdint.hpp> // boost::uintmax_t

using std::string;
using std::shared_ptr;
using boost::uintmax_t;

namespace base_game {

TextureResourceLoader::TextureResourceLoader() {
	logger::info("Create TextureResourceLoader");

}

TextureResourceLoader::~TextureResourceLoader() {
	logger::info("Destroy TextureResourceLoader");
}

bool TextureResourceLoader::vUseRawFile() {
	return false;
}

bool TextureResourceLoader::vDiscardRawBufferAfterLoad() {
	return true;
	//return false;
}

uintmax_t TextureResourceLoader::vGetLoadedResourceSize(char *rawBuffer,
		uintmax_t rawSize) {
	// This will keep the resource cache from allocating memory for the texture, so DirectX can manage it on it's own.
	return 0;
}

} /* namespace base_game */
