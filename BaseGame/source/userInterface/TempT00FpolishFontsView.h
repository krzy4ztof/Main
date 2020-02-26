/*
 * TempT00FpolishFontsView.h
 *
 *  Created on: 28 kwi 2019
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_
#define USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_

#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/FreeTypeCharacter.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "BaseUI.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <map> // std::map
#include <glm/glm.hpp> // glm::ivec2
#include <string> // std::string
#include <memory> // std::shared_ptr

namespace base_game {

class TempT00FpolishFontsUI: public BaseUI {
public:
	TempT00FpolishFontsUI(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempT00FpolishFontsUI();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();

	void temp_init_part();
	void temp_activate_part();
	void temp_deactivate_part();

	void temp_vOnRender(double fTime, float fElapsedTime);

protected:
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<FreeTypeRenderer> freeTypeRenderer;
	std::shared_ptr<ShaderCompiler> shaderCompiler;

};

class TempT00FpolishFontsView: public HumanView {
public:
	TempT00FpolishFontsView(std::shared_ptr<ResourceCache> resourceCache,
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempT00FpolishFontsView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);

	virtual void vTerminate();
//	virtual void vActivate();
//	virtual void vDeactivate();
	virtual void tempVRender(double fTime, float fElapsedTime);

protected:
	std::shared_ptr<TempT00FpolishFontsUI> tempT00FpolishFontsUI;
	/*
	std::shared_ptr<FreeTypeRenderer> freeTypeRenderer;
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	 */
};

/*
namespace temp_t00f_polish_fonts_view {
std::shared_ptr<TempT00FpolishFontsView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer);
}
 */

} /* namespace base_game */

#endif /* USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_ */
