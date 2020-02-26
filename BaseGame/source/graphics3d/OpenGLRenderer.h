/*
 * OpenGLRenderer.h
 *
 *  Created on: 17 sty 2020
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_OPENGLRENDERER_H_
#define GRAPHICS3D_OPENGLRENDERER_H_

#include "../gameInitialization/VideoSystemGLFW.h"

#include <memory> // shared_ptr

namespace base_game {

class OpenGLRenderer {
public:
	OpenGLRenderer(std::shared_ptr<VideoSystemGLFW> videoSystemGLFW);
	virtual ~OpenGLRenderer();

// You should leave this global - it does wacky things otherwise.
//static CDXUTDialogResourceManager g_DialogResourceManager;
//static CDXUTTextHelper* g_pTextHelper;
//virtual HRESULT VOnRestore()
//virtual ˜D3DRenderer11() { SAFE_DELETE(g_pTextHelper); }
	virtual bool vPreRender(); // more on this later!
	virtual bool vPostRender(); // more on this later!

private:
	std::shared_ptr<VideoSystemGLFW> videoSystemGLFW;
};

} /* namespace base_game */

#endif /* GRAPHICS3D_OPENGLRENDERER_H_ */
