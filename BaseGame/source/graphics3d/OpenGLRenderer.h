/*
 * OpenGLRenderer.h
 *
 *  Created on: 17 sty 2020
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_OPENGLRENDERER_H_
#define GRAPHICS3D_OPENGLRENDERER_H_

#include "../gameInitialization/VideoSystemGLFW.h"

#include "../resourceCache/ResourceCache.h"
#include "FiguresRenderer.h"
#include "ShaderResourceLoader.h"
#include "FreeTypeRenderer.h"
#include "TextureResourceLoader.h"
#include "TextureRenderer.h"
#include "CursorRenderer.h"

#include <memory> // shared_ptr

namespace base_game {

class OpenGLRenderer {
public:
	OpenGLRenderer(std::shared_ptr<VideoSystemGLFW> videoSystemGLFW,
			std::shared_ptr<ResourceCache> shrdPtrResourceCache);
	virtual ~OpenGLRenderer();

// You should leave this global - it does wacky things otherwise.
//static CDXUTDialogResourceManager g_DialogResourceManager;
//static CDXUTTextHelper* g_pTextHelper;
	virtual bool vOnRestore();
//virtual ˜D3DRenderer11() { SAFE_DELETE(g_pTextHelper); }
	virtual bool vPreRender(); // more on this later!
	virtual bool vPostRender(); // more on this later!


	void activateRenderers();
	void initRenderers();
// private:

	std::shared_ptr<VideoSystemGLFW> videoSystemGLFW;

	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<FiguresRenderer> figuresRenderer;
	std::shared_ptr<FreeTypeRenderer> freeTypeRenderer;

	//std::shared_ptr<SpriteSheet> spriteSheetLogo;
	std::shared_ptr<PngTextureLoader> pngTextureLoader;
	std::shared_ptr<PngRenderer> pngRenderer;

	std::shared_ptr<ShaderCompiler> shaderCompiler;

	std::shared_ptr<CursorRenderer> cursorRenderer;

private:


	void terminateRenderers();

};

} /* namespace base_game */

#endif /* GRAPHICS3D_OPENGLRENDERER_H_ */
