/*
 * TextureResourceLoader.h
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_TEXTURERESOURCELOADER_H_
#define GRAPHICS3D_TEXTURERESOURCELOADER_H_

#include "../resourceCache/IResourceExtraData.h"
#include "../resourceCache/IResourceLoader.h"
#include "../resourceCache/ResourceHandle.h"
#include "../resourceCache/ResourceCache.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <string> // string
#include <memory> // shared_ptr
#include <boost/gil/extension/io/Jpeg.hpp> // boost::gil::rgb8_image_t
#include <boost/gil/extension/io/png.hpp> // boost::gil::rgb8_image_t


namespace base_game {

class JpegResourceExtraData: public IResourceExtraData {
public:
	const static std::string CLASS_NAME;

	JpegResourceExtraData();
	virtual ~JpegResourceExtraData();

	virtual void loadImage(char* pRawBuffer, boost::uintmax_t rawSize);
	virtual boost::gil::rgb8_image_t getImage() {
		return rgb8_image;
	}

	virtual std::string vToString() {
		// return "JpegResourceExtraData";
		return CLASS_NAME;
	}

protected:
	boost::gil::rgb8_image_t rgb8_image;
};

class JpegResourceLoader: public IResourceLoader {
public:
	JpegResourceLoader();
	virtual ~JpegResourceLoader();

	virtual bool vUseRawFile() {
		return false;
		//return true;
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
	virtual std::string vGetPattern() {
		return "*.jpg";
	}

	virtual bool vAddNullZero() {
		//TODO: scriptLoader will return true
		return false;
	}

protected:

private:
};

/*
class TextureData {
public:
	TextureData();
	virtual ~TextureData();
	int width, height;
	float* data;
};
 */

//////////////////
class PngResourceExtraData: public IResourceExtraData {
public:
	const static std::string CLASS_NAME;

	PngResourceExtraData();
	virtual ~PngResourceExtraData();

	virtual void loadImage(char *pRawBuffer, boost::uintmax_t rawSize);
	// virtual void loadImage_222(char *pRawBuffer, boost::uintmax_t rawSize);
	virtual boost::gil::rgba8_image_t getImage() {
		return rgba8_image;
	}

	virtual std::string vToString() {
		// return "PngResourceExtraData";
		return CLASS_NAME;
	}

protected:
	boost::gil::rgba8_image_t rgba8_image;
};

class PngResourceLoader: public IResourceLoader {
public:
	PngResourceLoader();
	virtual ~PngResourceLoader();

	virtual bool vUseRawFile() {
		return false;
		//return true;
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
	virtual std::string vGetPattern() {
		return "*.png";
	}

	virtual bool vAddNullZero() {
		//TODO: scriptLoader will return true
		return false;
	}

protected:

private:
};

////////////////

class TextureLoader {
public:
	const static std::string GRAPHICS_FOLDER;

	TextureLoader(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TextureLoader();

	virtual void init(std::string fileName);
//	void debugCopyImageJpg(boost::gil::rgb8_image_t imageData);
	virtual void activate();
	void deactivate();
	void terminate();
protected:
	std::shared_ptr<IResourceExtraData> loadImage(std::string fileName);
	// void image_to_texture(float * data);
	// std::shared_ptr<IResourceExtraData> resourceExtraData; // zamiast rgb8_image
// private:
	GLuint texture;
	// boost::gil::rgb8_image_t rgb8_image;
	//boost::gil::rgba8_image_t rgba8_image;
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
};

class JpgTextureLoader: public TextureLoader {
public:
	JpgTextureLoader(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~JpgTextureLoader();

	void debugCopyImageJpg(boost::gil::rgb8_image_t imageData);
	virtual void init(std::string fileName);
	virtual void activate();
protected:
	boost::gil::rgb8_image_t rgb8_image;
	virtual void image_to_texture(float *data);
};

class PngTextureLoader: public TextureLoader {
public:
	PngTextureLoader(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~PngTextureLoader();

	void debugCopyImagePng(boost::gil::rgba8_image_t imageData);
	virtual void init(std::string fileName);
	virtual void activate();
protected:
	boost::gil::rgba8_image_t rgba8_image;
	virtual void image_to_texture(float *data);
};

namespace jpeg_resource_loader {
std::shared_ptr<IResourceLoader> createJpegResourceLoader();
} /* namespace jpeg_resource_loader */

namespace png_resource_loader {
std::shared_ptr<IResourceLoader> createPngResourceLoader();
} /* namespace png_resource_loader */


} /* namespace base_game */

#endif /* GRAPHICS3D_TEXTURERESOURCELOADER_H_ */
