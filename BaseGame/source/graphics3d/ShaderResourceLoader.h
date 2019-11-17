/*
 * ShaderResourceLoader.h
 *
 *  Created on: 3 maj 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_SHADERRESOURCELOADER_H_
#define GRAPHICS3D_SHADERRESOURCELOADER_H_

#include "../resourceCache/IResourceExtraData.h"
#include "../resourceCache/IResourceLoader.h"
#include "../resourceCache/ResourceHandle.h"
#include "../resourceCache/ResourceCache.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <memory> // shared_ptr
#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {

class ShaderResourceExtraData: public IResourceExtraData {
public:
	ShaderResourceExtraData();
	virtual ~ShaderResourceExtraData();

	virtual void compileShader(char* pRawBuffer, boost::uintmax_t rawSize)=0;
	virtual GLuint getShaderId() {
		return shaderId;
	}

protected:
	GLuint shaderId;
};

class VertexShaderResourceExtraData: public ShaderResourceExtraData {
public:
	VertexShaderResourceExtraData();
	virtual ~VertexShaderResourceExtraData();

	virtual std::string vToString() {
		return "VertexShaderResourceExtraData";
	}

	virtual void compileShader(char* pRawBuffer, boost::uintmax_t rawSize);
	virtual GLuint getShaderId() {
		return ShaderResourceExtraData::getShaderId();
	}

	/*
	 boost::property_tree::ptree* getRoot() {
	 return m_pPtree;
	 };
	 */

protected:

private:

};

class FragmentShaderResourceExtraData: public ShaderResourceExtraData {
public:
	FragmentShaderResourceExtraData();
	virtual ~FragmentShaderResourceExtraData();

	virtual std::string vToString() {
		return "FragmentShaderResourceExtraData";
	}

	virtual void compileShader(char* pRawBuffer, boost::uintmax_t rawSize);
	virtual GLuint getShaderId() {
		return ShaderResourceExtraData::getShaderId();
	}

	/*
	 boost::property_tree::ptree* getRoot() {
	 return m_pPtree;
	 };
	 */

protected:

private:

};

class ShaderResourceLoader: public IResourceLoader {
public:
	ShaderResourceLoader();
	virtual ~ShaderResourceLoader();

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
			std::shared_ptr<ResourceHandle> handle) = 0;
	virtual std::string vGetPattern() = 0;

	virtual bool vAddNullZero() {
		//TODO: scriptLoader will return true
		return true;
	}

protected:

private:
};

class VertexShaderResourceLoader: public ShaderResourceLoader {
public:
	VertexShaderResourceLoader();
	virtual ~VertexShaderResourceLoader();

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);
	virtual std::string vGetPattern();
};

class FragmentShaderResourceLoader: public ShaderResourceLoader {
public:
	FragmentShaderResourceLoader();
	virtual ~FragmentShaderResourceLoader();

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);
	virtual std::string vGetPattern();
};

class ShaderCompiler {
public:
	const static std::string SHADERS_FOLDER;

	ShaderCompiler(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~ShaderCompiler();
	GLuint loadShaders(std::string vertexShaderName,
			std::string fragmentShaderName);

protected:
	GLuint loadVertexShader(std::string vertexShaderName);
	GLuint loadFragmentShader(std::string fragmentShaderName);
	std::shared_ptr<IResourceExtraData> loadShader(
			std::string vertexShaderName);

private:
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
};

namespace vertex_shader_resource_loader {
std::shared_ptr<IResourceLoader> createVertexShaderResourceLoader();
} /* namespace vertex_shader_resource_loader */

namespace fragment_shader_resource_loader {
std::shared_ptr<IResourceLoader> createFragmentShaderResourceLoader();
} /* namespace fragment_shader_resource_loader */

} /* namespace base_game */

#endif /* GRAPHICS3D_SHADERRESOURCELOADER_H_ */
