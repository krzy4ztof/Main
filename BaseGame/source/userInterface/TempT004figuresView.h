/*
 * T004figuresView.h
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#ifndef BASIC_TEMPT004FIGURESVIEW_H_
#define BASIC_TEMPT004FIGURESVIEW_H_

#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "BaseUI.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> //string
#include <memory> // shared_ptr

namespace base_game {
// see: Temp06View.h

class TempT004figuresUI: public BaseUI {
public:
	TempT004figuresUI(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempT004figuresUI();

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
	std::shared_ptr<ShaderCompiler> shaderCompiler;

};

class TempT004figuresView: public HumanView {
public:
	TempT004figuresView(std::shared_ptr<ResourceCache> resourceCache,
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempT004figuresView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
	//virtual void vActivate();
	//virtual void vDeactivate();

	virtual void tempVRender(double fTime, float fElapsedTime);

protected:
	//std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	//std::shared_ptr<FiguresRenderer> figuresRenderer;
	std::shared_ptr<TempT004figuresUI> tempT004figuresUI;
};

/*
namespace temp_t004_figures_view {
std::shared_ptr<TempT004figuresView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer);
}
 */

} /* namespace base_game */

#endif /* BASIC_TEMPT004FIGURESVIEW_H_ */
