/*
 * T00DpngGilScanlineView.h
 *
 *  Created on: 20 kwi 2019
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_
#define USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_

// #include "../main/IOpenGLView.h"
#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3D/TextureResourceLoader.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <boost/gil/extension/io/png.hpp> // boost::gil::rgb8_image_t

namespace base_game {

//class T00DpngGilScanlineView: public IOpenGLView {
class TempT00DpngGilScanlineView: public HumanView {
public:
	// TempT00DpngGilScanlineView();
	TempT00DpngGilScanlineView(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempT00DpngGilScanlineView();

	virtual void vInit();
	// virtual void vRender(double fTime, float fElapsedTime);
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
	virtual void vActivate();
	virtual void vDeactivate();

protected:
	// GLuint vertex_array_object;
	GLuint programID;
	GLuint vao; // vertex_array_object
	GLuint position_buffer;
	GLuint index_buffer;

	GLuint texture;
	GLuint uvbuffer;

	// boost::gil::rgba8_image_t rgba8_image; // boost::gil::image

	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	PngTextureLoader *pngTextureLoader;

	// void image_to_texture(float * data);

	// void loadTexture();
	// void testCopyImage();
	// void readImageInfo();
	// void loadImage();

};

namespace temp_t00d_png_gil_scanline_view {
//TempT00DpngGilScanlineView* getView(bool reset);
std::shared_ptr<TempT00DpngGilScanlineView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache);
}

} /* namespace base_game */

#endif /* USERINTERFACE_TEMPT00DPNGGILSCANLINEVIEW_H_ */
