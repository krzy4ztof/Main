/*
 * T00DpngGilScanlineView.h
 *
 *  Created on: 20 kwi 2019
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_
#define USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_

#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "TempUI.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <boost/gil/extension/io/png.hpp> // boost::gil::rgb8_image_t

namespace base_game {
class TempT00DpngGilScanlineUI: public TempUI {
public:
	TempT00DpngGilScanlineUI(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempT00DpngGilScanlineUI();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();

	void temp_init_part();
	void temp_activate_part();
	void temp_vOnRender(double fTime, float fElapsedTime);

protected:
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<SpriteSheet> spriteSheet;

	PngTextureLoader *pngTextureLoader;
	std::shared_ptr<PngRenderer> pngRenderer;
	std::shared_ptr<ShaderCompiler> shaderCompiler;

};

class TempT00DpngGilScanlineView: public HumanView {
public:
	TempT00DpngGilScanlineView(std::shared_ptr<ResourceCache> resourceCache,
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempT00DpngGilScanlineView();

	virtual void vInit();
	// virtual void vRender(double fTime, float fElapsedTime);
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
//	virtual void vActivate();
//	virtual void vDeactivate();
	virtual void tempVRender(double fTime, float fElapsedTime);

protected:
	std::shared_ptr<TempT00DpngGilScanlineUI> tempT00DpngGilScanlineUI;
	/*
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<SpriteSheet> spriteSheet;

	PngTextureLoader *pngTextureLoader;
	std::shared_ptr<PngRenderer> pngRenderer;
	 */
};

/*
namespace temp_t00d_png_gil_scanline_view {
std::shared_ptr<TempT00DpngGilScanlineView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer);
}
 */

} /* namespace base_game */

#endif /* USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_ */
