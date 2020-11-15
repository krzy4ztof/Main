/*
 * T008jpegGilTextureView.h
 *
 *  Created on: 10 lut 2019
 *      Author: Krzysztof
 */

#ifndef BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_
#define BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_

#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "TempUI.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint
#include <memory> // shared_ptr

#include <boost/gil/extension/io/jpeg.hpp> // boost::gil::rgb8_image_t


namespace base_game {
// see Temp03gilView.h
class TempT009jpegGilTextureUI: public TempUI {
public:
	//TempT009jpegGilTextureUI(std::shared_ptr<ResourceCache> resourceCache);
	TempT009jpegGilTextureUI(
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempT009jpegGilTextureUI();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual int vGetZOrder() const;
	virtual void vSetZOrder(int const zOrder) const;
	virtual void vTerminate();

	void temp_init_part();
	void temp_activate_part();
	void temp_vOnRender(double fTime, float fElapsedTime);

protected:
	std::shared_ptr<OpenGLRenderer> openGLRenderer;

	std::shared_ptr<SpriteSheet> spriteSheet;
	std::shared_ptr<SpriteSheet> spriteSheet2;

	/*
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	JpegTextureLoader *jpegTextureLoader;

	std::shared_ptr<JpegRenderer> jpegRenderer;
	std::shared_ptr<ShaderCompiler> shaderCompiler;
	 */
};


class TempT009jpegGilTextureView: public HumanView {
public:
	TempT009jpegGilTextureView(std::shared_ptr<ResourceCache> resourceCache,
			std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~TempT009jpegGilTextureView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
//	virtual void vActivate();
	void vActivateOK();
//	virtual void vDeactivate();
	virtual void tempVRender(double fTime, float fElapsedTime);


protected:
	std::shared_ptr<TempT009jpegGilTextureUI> tempT009jpegGilTextureUI;
	/*
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	JpegTextureLoader *jpegTextureLoader;

	std::shared_ptr<SpriteSheet> spriteSheet;
	std::shared_ptr<SpriteSheet> spriteSheet2;
	std::shared_ptr<JpegRenderer> jpegRenderer;
	 */
};

/*
namespace temp_t009_jpeg_gil_texture_view {
std::shared_ptr<TempT009jpegGilTextureView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer);
}
 */

} /* namespace base_game */

#endif /* BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_ */
