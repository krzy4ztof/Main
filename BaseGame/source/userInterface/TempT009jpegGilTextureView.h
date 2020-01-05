/*
 * T008jpegGilTextureView.h
 *
 *  Created on: 10 lut 2019
 *      Author: Krzysztof
 */

#ifndef BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_
#define BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_

//#include "../main/IOpenGLView.h"
#include "HumanView.h"
#include "../resourceCache/ResourceCache.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/TextureRenderer.h"
//#include "../graphics3d/SpriteSheet.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint
#include <memory> // shared_ptr

#include <boost/gil/extension/io/jpeg.hpp> // boost::gil::rgb8_image_t


namespace base_game {
// see Temp03gilView.h

class TempT009jpegGilTextureView: public HumanView {
public:
	TempT009jpegGilTextureView(std::shared_ptr<ResourceCache> resourceCache);
	virtual ~TempT009jpegGilTextureView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
	virtual void vActivate();
	//void vActivateOK_jpeg();
	void vActivateOK();
	virtual void vDeactivate();

protected:
	/*
	// GLuint vertex_array_object;
	GLuint programID;
	GLuint vao; // vertex_array_object
	GLuint position_buffer;
	GLuint index_buffer;

	// GLuint texture;
	GLuint uvbuffer;
	 */


	// boost::gil::rgb8_image_t rgb8_image; // boost::gil::image
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	JpegTextureLoader *jpegTextureLoader;
	// JpegTextureLoader *jpegTextureLoader2;

	std::shared_ptr<SpriteSheet> spriteSheet;
	std::shared_ptr<SpriteSheet> spriteSheet2;


	std::shared_ptr<JpegRenderer> jpegRenderer;
	// void generate_texture(float * data, int width, int height);
	//void image_to_texture(float * data);

	// void loadTexture();
	//void testCopyImage();

};

namespace temp_t009_jpeg_gil_texture_view {
//TempT009jpegGilTextureView*
std::shared_ptr<TempT009jpegGilTextureView> getView(bool reset,
		std::shared_ptr<ResourceCache> resourceCache);
}

} /* namespace base_game */

#endif /* BASIC_TEMPT009JPEGGILTEXTUREVIEW_H_ */
