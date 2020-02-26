/*
 * T004figuresView.h
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#ifndef BASIC_TEMPCOMBINEDVIEW_H_
#define BASIC_TEMPCOMBINEDVIEW_H_

//#include "../main/IOpenGLView.h"
#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "BaseUI.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> //string
#include <memory> // shared_ptr

namespace base_game {

class TempCombinedUI: public BaseUI {
public:
	TempCombinedUI(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempCombinedUI();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;

	void temp_init_part();
	void temp_activate_part();
	void temp_vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();

protected:

	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<FiguresRenderer> figuresRenderer;
	std::shared_ptr<FreeTypeRenderer> freeTypeRenderer;

	std::shared_ptr<JpegTextureLoader> jpegTextureLoader;
	std::shared_ptr<PngTextureLoader> pngTextureLoader;

	std::shared_ptr<JpegRenderer> jpegRenderer;
	std::shared_ptr<PngRenderer> pngRenderer;

	std::shared_ptr<SpriteSheet> spriteSheet;
	std::shared_ptr<SpriteSheet> spriteSheet2;

	std::shared_ptr<SpriteSheet> spriteSheetPng;
	std::shared_ptr<ShaderCompiler> shaderCompiler;

};

class TempCombinedView: public HumanView {
public:
	TempCombinedView(std::shared_ptr<ResourceCache> resourceCache,
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempCombinedView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);

	void temp_render(double fTime, float fElapsedTime);
	virtual void tempVRender(double fTime, float fElapsedTime);

	virtual void vTerminate();
//	virtual void vActivate();
//	virtual void vDeactivate();



protected:
	std::shared_ptr<TempCombinedUI> tempCombinedUI;

};

/*
namespace temp_combined_view {
std::shared_ptr<TempCombinedView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer);
}
 */

} /* namespace base_game */

#endif /* BASIC_TEMPCOMBINEDVIEW_H_ */
