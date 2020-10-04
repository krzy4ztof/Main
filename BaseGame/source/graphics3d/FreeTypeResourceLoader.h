/*
 * FreeTypeResourceLoader.h
 *
 *  Created on: 10 lis 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_FREETYPERESOURCELOADER_H_
#define GRAPHICS3D_FREETYPERESOURCELOADER_H_

#include "../resourceCache/IResourceExtraData.h"
#include "../resourceCache/IResourceLoader.h"
#include "../resourceCache/ResourceHandle.h"
#include "../resourceCache/ResourceCache.h"
#include "FreeTypeCharacter.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <memory> // shared_ptr
#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <map> // std::map

#include <ft2build.h>
#include FT_FREETYPE_H

namespace base_game {

class FreeTypeResourceExtraData: public IResourceExtraData {
public:
	FreeTypeResourceExtraData();
	virtual ~FreeTypeResourceExtraData();

	void loadFtNewFace(char *rawBuffer, uintmax_t rawSize);

	virtual std::string vToString() {
		return "FreeTypeResourceExtraData";
	}
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> getCharacters() {
		return characters;
	}

	void debugCharacters();

protected:
	void initCharacter(FT_Face face, FT_ULong char_code);
	void initFreetypeCharacters(FT_Face face);
	void initCharacter(FT_Face face, FT_ULong char_code,
			GLushort char_code_out);

private:
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters;
};

class FreeTypeResourceLoader: public IResourceLoader {
public:
	FreeTypeResourceLoader();
	virtual ~FreeTypeResourceLoader();

	virtual bool vUseRawFile() {
		return false;
	}

	virtual bool vDiscardRawBufferAfterLoad() {
		return true;
	}

	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize) {
		return rawSize;
	}

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);
	virtual std::string vGetPattern();

	virtual bool vAddNullZero() {
		return true;
	}
};

class FreeTypeLoader {
public:
	const static std::string FONTS_FOLDER;


	FreeTypeLoader(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~FreeTypeLoader();

	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> initFreetype();
	void debugCharacters();

protected:
	std::shared_ptr<IResourceExtraData> loadFont(std::string vertexShaderName);

private:
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters;

};

namespace free_type_resource_loader {
std::shared_ptr<IResourceLoader> createFreeTypeResourceLoader();
}

} /* namespace base_game */

#endif /* GRAPHICS3D_FREETYPERESOURCELOADER_H_ */
