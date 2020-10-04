/*
 * OpenGLRenderer.cpp
 *
 *  Created on: 17 sty 2020
 *      Author: Krzysztof
 */

#include "OpenGLRenderer.h"
#include "../debugging/Logger.h"

#include "../resourceCache/ResourceCache.h"
#include "FiguresRenderer.h"
#include "ShaderResourceLoader.h"
#include "FreeTypeRenderer.h"
#include "FreeTypeResourceLoader.h"
#include "FreeTypeCharacter.h"
#include "TextureResourceLoader.h"
#include "TextureRenderer.h"

#include <sstream>      // std::stringstream
#include <memory> // shared_ptr

using std::stringstream;
using std::shared_ptr;
using std::make_shared;

namespace base_game {

OpenGLRenderer::OpenGLRenderer(shared_ptr<VideoSystemGLFW> videoSystemGLFW,
		shared_ptr<ResourceCache> shrdPtrResourceCache) {
	logger::info("Create OpenGLRenderer");
	this->videoSystemGLFW = videoSystemGLFW;
	this->shrdPtrResourceCache = shrdPtrResourceCache;



	figuresRenderer = make_shared<FiguresRenderer>();
	freeTypeRenderer = make_shared<FreeTypeRenderer>();
	pngTextureLoader = make_shared<PngTextureLoader>(
			this->shrdPtrResourceCache);
	pngRenderer = make_shared<PngRenderer>();
	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);
	cursorRenderer = make_shared<CursorRenderer>();

	//this->initRenderers();
}

OpenGLRenderer::~OpenGLRenderer() {
	logger::info("Destroy OpenGLRenderer");

	terminateRenderers();
	shrdPtrResourceCache.reset();
	videoSystemGLFW.reset();
	logger::info("END Destroy OpenGLRenderer");
}

/**
 * Should not be invoked before videoSystemGLFW->initialize();
 */
void OpenGLRenderer::initRenderers() {
	stringstream ss;

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler->loadShaders("figures_renderer");
	figuresRenderer->init(programID);

	// vActivate();

	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	GLuint freeTypeProgramID = shaderCompiler->loadShaders("fonts_renderer");

	freeTypeRenderer->init(freeTypeProgramID, characters);
	freeTypeRenderer->debugCharacters();

	// --------
//	pngTextureLoader->init("intro_watermill.png", spriteSheetLogo);

	GLuint pngProgramID = shaderCompiler->loadShaders("texture_renderer");
	pngRenderer->init(pngProgramID);

	cursorRenderer->init(videoSystemGLFW->getWindow());
}

void OpenGLRenderer::terminateRenderers() {
	stringstream ss;
	//this->deactivateRenderer();

	if (shaderCompiler) {
		/*
		 * There is some bug in
		 * (Fragment/Vertex)ShaderResourceExtraData::compileShader
		 * so, we need to remove shaders here.
		 * In this way in the method
		 * ResourceCache::getHandle(Resource *resource)
		 * we need to call handle = load(resource); each time we compile shader
		 * load(resource) invokes
		 * FragmentShaderResourceExtraData::compileShader(char *pRawBuffer, uintmax_t rawSize)
		 * and
		 * VertexShaderResourceExtraData::compileShader(char *pRawBuffer, uintmax_t rawSize)
		 * these methods are important to successfully load shader again
		 *
		 * The bug should be fixed and we should not removeShaders("figures_renderer") here
		 * VertexShaderResourceExtraData::compileShader should save results in the cache for further usage
		 *
		 */

		shaderCompiler->removeShaders("fonts_renderer");
		shaderCompiler->removeShaders("figures_renderer");
		shaderCompiler->removeShaders("texture_renderer");
	} else {
		logger::info("shader compiler destroyed");
	}
	shaderCompiler.reset();
	freeTypeRenderer.reset();
	figuresRenderer.reset();

	pngRenderer.reset();
	pngTextureLoader->terminate();
	pngTextureLoader.reset();
//	spriteSheetLogo.reset();

//	shrdPtrResourceCache.reset();
}

bool OpenGLRenderer::vPreRender() {
	// Start scene

	
	return videoSystemGLFW->preRender();
}

bool OpenGLRenderer::vPostRender() {
	// End scene
	return videoSystemGLFW->postRender();
}

bool OpenGLRenderer::vOnRestore() {
	// End scene

	return true;
}


} /* namespace base_game */
